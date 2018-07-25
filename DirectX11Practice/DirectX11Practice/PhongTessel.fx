struct VS_INPUT
{
	float3 Pos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct HullInput
{
	float3 Pos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct PixelInput
{
	float4 Pos: SV_POSITION;
	float4 WorldPos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float4 lightViewPos : POSITION1;
	float3 lightPos : POSITION2;
	float2 projectTexCoord: POSITION3;

};

struct HS_PATCH_DATA
{
	float edges[3] : SV_TessFactor;
	float inside : SV_InsideTessFactor;
	float2 TexCoord[3]: TEXCOORD;
	float3 Normal[3] : NORMAL;
	float3 Tangent[3] : TANGENT;
};

struct DS_ControlPointInput 
{
	float3 Pos : BEZIERPOS;
};


struct s_Light
{
	float4 Dir;
	float3 Attenuation;
	float Cone;
	float4 Pos;
	float4 Ambient;
	float4 Diffuse;
	float4x4 lightView;
	float4x4 lightProj;
};


cbuffer LightConstantBuffer : register(b0)
{
	s_Light Light[5];
};

cbuffer ConstantBuffer : register(b1)
{
	float4x4 WVP;
	float4x4 World;
	float4x4 lightView;
	float4x4 lightProjection;
	float4 Diffuse;
	float4 CamPos;
	bool HasTexture;
	bool HasNormalMap;
	bool IsPhongTessel;

};

Texture2D objTexture: register(t0);
Texture2D objNormalMap: register(t1);
Texture2D objNormalMap1: register(t2);
TextureCube SkyMap: register(t3);
Texture2D flashLightShadowMap: register(t4);
Texture2D spotLightShadowMap: register(t5);
SamplerState objSamplerState : register(s0); //WRAP
SamplerState objSamplerClamp : register(s1); //CLAMP

float3 SpotLight(PixelInput input, s_Light light);


HS_PATCH_DATA PatchConstantFunction(InputPatch<HullInput, 3> controlPoints);


HullInput PhongVS(VS_INPUT input)
{
	HullInput output;
	output.Pos = input.Pos;
	output.TexCoord = input.TexCoord;
	output.Normal = input.Normal;
	output.Tangent = input.Tangent;

	return output;
}

//constant function
HS_PATCH_DATA PatchConstantFunction(InputPatch<HullInput, 3> controlPoints)
{
	HS_PATCH_DATA patch = (HS_PATCH_DATA)0;

	float3 roundedEdgeTessFactor;
	float roundedInsideTessFactor, insideTessFactor;
	float tessel;
	if (IsPhongTessel) tessel = 5.0f;
	else tessel = 0.0f;
	ProcessTriTessFactorsMax((float3)tessel, 1.0f, roundedEdgeTessFactor, roundedInsideTessFactor, insideTessFactor);
	patch.edges[0] = roundedEdgeTessFactor.x;
	patch.edges[1] = roundedEdgeTessFactor.y;
	patch.edges[2] = roundedEdgeTessFactor.z;
	patch.inside = roundedInsideTessFactor;

	for (int i = 0; i < 3; i++)
	{
		patch.TexCoord[i] = controlPoints[i].TexCoord;
		patch.Normal[i] = controlPoints[i].Normal;
		patch.Tangent[i] = controlPoints[i].Tangent;
	}

	return patch;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]

DS_ControlPointInput PhongHS(InputPatch<HullInput, 3> patch, uint pointId :	SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	DS_ControlPointInput output;
	output.Pos = patch[pointId].Pos;

	return output;
}



float2 BarycentricInterpolate(float2 v0, float2 v1, float2 v2, float3 barycentric)
{
	return barycentric.z * v0 + barycentric.x * v1 + barycentric.y * v2;
}

float2 BarycentricInterpolate(float2 v[3], float3 barycentric)
{
	return BarycentricInterpolate(v[0], v[1], v[2], barycentric);
}

float3 BarycentricInterpolate(float3 v0, float3 v1, float3 v2, float3 barycentric)
{
	return barycentric.z * v0 + barycentric.x * v1 + barycentric.y * v2;
}

float3 BarycentricInterpolate(float3 v[3], float3 barycentric)
{
	return BarycentricInterpolate(v[0], v[1], v[2], barycentric);
}

float4 BarycentricInterpolate(float4 v0, float4 v1, float4 v2, float3 barycentric)
{
	return barycentric.z * v0 + barycentric.x * v1 + barycentric.y * v2;
}

float4 BarycentricInterpolate(float4 v[3], float3 barycentric)
{
	return BarycentricInterpolate(v[0], v[1], v[2], barycentric);
}

float3 ProjectOntoPlane(float3 planeNormal, float3 planePoint, float3 pointToProject)
{
	return pointToProject - dot(pointToProject - planePoint, planeNormal) * planeNormal;
}

[domain("tri")]
PixelInput PhongDS(HS_PATCH_DATA patchData, const OutputPatch<DS_ControlPointInput, 3> patch, float3 uvwCoord: SV_DomainLocation)
{
	PixelInput output;
	float3 Pos = BarycentricInterpolate(patch[0].Pos, patch[1].Pos, patch[2].Pos, uvwCoord);
	float2 TexCoord = BarycentricInterpolate(patchData.TexCoord, uvwCoord);
	float3 Normal = BarycentricInterpolate(patchData.Normal, uvwCoord);
	float3 Tangent = BarycentricInterpolate(patchData.Tangent, uvwCoord);

	float3 posProjectedU = ProjectOntoPlane(patchData.Normal[0], patch[0].Pos, Pos);
	float3 posProjectedV = ProjectOntoPlane(patchData.Normal[1], patch[1].Pos, Pos);
	float3 posProjectedW = ProjectOntoPlane(patchData.Normal[2], patch[2].Pos, Pos);

	Pos = BarycentricInterpolate(posProjectedU, posProjectedV, posProjectedW, uvwCoord);
	output.Pos = mul(float4(Pos, 1.0f), WVP);
	output.WorldPos = mul(float4(Pos, 1.0f), World);
	output.Normal = mul(normalize(Normal), World);
	output.Tangent = mul(normalize(Tangent), World);
	output.TexCoord = mul(TexCoord, World);

	float2 projectTexCoord;
	output.projectTexCoord.x = ((output.Pos.x / output.Pos.w) / 2.0f) + 0.5f;
	output.projectTexCoord.y = -((output.Pos.y / output.Pos.w) / 2.0f) + 0.5f;

	return output;

}

float4 PhongPS(PixelInput input) : SV_TARGET
{
	input.Normal = normalize(input.Normal);

	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 finalAmbient;
	float3 spotLight = SpotLight(input, Light[3]);
	float3 flashLight = SpotLight(input, Light[4]);
	//float3 flashLight = float3(1.0f, 0.0f, 0.0f);
	float4 textDiffuse;
	if (HasTexture)
	textDiffuse = objTexture.Sample(objSamplerState, input.TexCoord);
	
	
	if (HasNormalMap)
	{
		float4 normalMap = objNormalMap.Sample(objSamplerState, input.TexCoord);
		//change normal map range from [0, 1] to [-1, 1]
		normalMap = (2.0f * normalMap) - 1.0f;
	
		input.Tangent = normalize(input.Tangent - dot(input.Tangent, input.Normal) * input.Normal);
		//create biTangent
		float3 biTangent = cross(input.Normal, input.Tangent);
		//create the "Texture Space"
		float3x3 texSpace = float3x3(input.Tangent, biTangent, input.Normal);
	
		input.Normal = normalize(mul(normalMap, texSpace));
	}
	
	float2 projectTexCoord;
	float spotLightShadowValue;
	float flashlightShadowValue;
	float3 flashlightColor;
	float3 spotlightColor;
	projectTexCoord.x = ((input.Pos.x / input.Pos.w) / 2.0f) + 0.5f;
	projectTexCoord.y = -((input.Pos.y / input.Pos.w) / 2.0f) + 0.5f;

	flashlightShadowValue = flashLightShadowMap.Sample(objSamplerClamp, input.projectTexCoord).r;

	spotLightShadowValue = spotLightShadowMap.Sample(objSamplerClamp, input.projectTexCoord).r;

	//combine light and texture color
	finalAmbient = textDiffuse *float3(0.6f, 0.6f, 0.6f);
	spotlightColor = saturate(spotLight) * spotLightShadowValue;

	flashlightColor = saturate(flashLight) * flashlightShadowValue;

	finalColor = saturate(spotlightColor + flashlightColor + finalAmbient);
	
	
	return float4(finalColor, textDiffuse.a);
}

float edgeLod(float3 pos1, float3 pos2) { return dot(pos1, pos2); }


float3 SpotLight(PixelInput input, s_Light light) :SV_Target
{
	//input.Normal = normalize(input.Normal);
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);

	float3 lightToPixel = light.Pos.xyz - input.WorldPos.xyz; // object -> light
	float d = length(lightToPixel);

	float temp = 1.0f;
	if (d > 10)
		temp = 10 / d;

	lightToPixel /= d;

	float surfaceRatio = saturate(dot(-lightToPixel, normalize(light.Dir)));
	//float sin, cos;
	//sincos(light.Cone, sin, cos);
	//if (surfaceRatio < cos)
	//	return finalColor;
	float3 spotFactor = pow(max(surfaceRatio, 0.0f),light.Cone);
	float3 lightRatio = saturate(dot(normalize(lightToPixel), input.Normal));

	return temp * spotFactor * lightRatio * light.Diffuse  * light.Ambient / (light.Attenuation[0] + (light.Attenuation[1] * d) + (light.Attenuation[2] * (d * d)));


}

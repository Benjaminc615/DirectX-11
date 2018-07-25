struct VS_INPUT
{
	float3 Pos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct HullInputType
{
	float3 Pos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct PS_INPUT
{
	float4 Pos: SV_POSITION;
	float4 WorldPos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct HS_OUTPUT
{
	float3 Pos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};


struct ConstantOutput
{
	float edges[3] : SV_TessFactor;
	float inside : SV_InsideTessFactor;
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
	float4 CamPos;
	bool HasTexture;
	bool HasNormalMap;
};

//declaring variables 
Texture2D objTexture: register(t0);
Texture2D objNormalMap: register(t1);
//Texture2D objDepthMap: register(t2);
Texture2D objShadowMap: register(t2);
SamplerState objSamplerState : register(s0); //WRAP

float3 SpotLight(PS_INPUT input, s_Light light);
float3 PointLight(PS_INPUT input, s_Light light);
float3 DirectLight(PS_INPUT input, s_Light light);


HullInputType TerrainVS(VS_INPUT input)
{
	HullInputType output;
	output.Pos = input.Pos;
	output.TexCoord = input.TexCoord;
	output.Normal = input.Normal;
	output.Tangent = input.Tangent;

	return output;
}

ConstantOutput PatchConstantFunction(InputPatch<HullInputType, 3> inputPatch, uint patchId : SV_PrimitiveID)
{
	ConstantOutput output;

	float3 centerL = (inputPatch[0].Pos + inputPatch[1].Pos + inputPatch[2].Pos) * 0.3333f;
	float3 centerW = mul(float4(centerL, 1.0f), World).xyz;
	float d = distance(centerW, CamPos);
	float d0 = 10.0f;
	float d1 = 120.0f;
	float s = saturate((d - d0) / (d1 - d0));;
	float tess = pow(2 , lerp(6, 0, s)); // d = 10, 50, 100

	output.edges[0] = tess;
	output.edges[1] = tess;
	output.edges[2] = tess;
	output.inside = tess;

	return output;
}

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]

HS_OUTPUT TerrainHS(InputPatch<HullInputType, 3> patch, uint pointId :	SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	HS_OUTPUT output;
	output.Pos = patch[pointId].Pos;
	output.TexCoord = patch[pointId].TexCoord;
	output.Normal = patch[pointId].Normal;
	output.Tangent = patch[pointId].Tangent;

	return output;
}
[domain("tri")]

PS_INPUT TerrainDS(ConstantOutput input, float3 uvwCoord: SV_DomainLocation, const OutputPatch<HS_OUTPUT, 3> patch)
{
	PS_INPUT output;
	float3 vertPos;
	vertPos = uvwCoord.x * patch[0].Pos + uvwCoord.y * patch[1].Pos + uvwCoord.z * patch[2].Pos;
	output.TexCoord = uvwCoord.x * patch[0].TexCoord + uvwCoord.y * patch[1].TexCoord + uvwCoord.z * patch[2].TexCoord;
	output.Normal = uvwCoord.x * patch[0].Normal + uvwCoord.y * patch[1].Normal + uvwCoord.z * patch[2].Normal;
	output.Tangent = uvwCoord.x * patch[0].Tangent + uvwCoord.y * patch[1].Tangent + uvwCoord.z * patch[2].Tangent;
	
	output.Pos = mul(float4(vertPos,1.0f), WVP);
	output.WorldPos = mul(float4(vertPos, 1.0f), World);
	output.TexCoord = mul(output.TexCoord, World);
	output.Normal = mul(output.Normal, World);
	output.Tangent = mul(output.Tangent, World);

	return output;

}


float4 TerrainPS(PS_INPUT input) : SV_TARGET
{
	input.Normal = normalize(input.Normal);

	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 finalAmbient;
	float3 DirLight = DirectLight(input, Light[1]);
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

	//combine light and texture color
	finalAmbient = textDiffuse * float3(0.3f, 0.3f, 0.3f);
	finalColor = saturate(saturate(DirLight) + finalAmbient);


	return float4(finalColor, textDiffuse.a);
}



float3 SpotLight(PS_INPUT input, s_Light light) :SV_Target
{
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);

	float3 lightToPixel = light.Pos.xyz - input.WorldPos.xyz; // piexl -> light
	float d = length(lightToPixel);

	lightToPixel /= d;

	float surfaceRatio = saturate(dot(-lightToPixel, normalize(light.Dir)));

	float3 spotFactor = pow(max(surfaceRatio, 0.0f),light.Cone);
	float3 lightRatio = saturate(dot(normalize(lightToPixel), input.Normal));

	return spotFactor * lightRatio * light.Diffuse  * light.Ambient / (light.Attenuation[0] + (light.Attenuation[1] * d) + (light.Attenuation[2] * (d * d)));


}

float3 PointLight(PS_INPUT input, s_Light light) :SV_Target
{
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 lightToPixel = light.Pos.xyz - input.WorldPos.xyz;
	float d = length(lightToPixel);

	lightToPixel /= d;

	float ratio = saturate(dot(lightToPixel, input.Normal));
	return ratio * light.Diffuse * light.Ambient / (light.Attenuation[0] + (light.Attenuation[1] * d) + (light.Attenuation[2] * (d * d)));

}

float3 DirectLight(PS_INPUT input, s_Light light) :SV_Target
{
	float3 lightToPixel = -light.Dir;

	float ratio = saturate(dot(lightToPixel, input.Normal));
	return ratio * light.Diffuse * light.Ambient;


}
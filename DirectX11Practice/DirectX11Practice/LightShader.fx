struct PS_INPUT
{
	float4 Pos: SV_POSITION;
	float4 WorldPos: POSITION;
	float2 TexCoord: TEXCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float4 ViewPos : POSITION1;
	float3 lightPos : POSITION2;

};

struct depthVSInput
{
	float3 position : POSITION;
};

struct depthPSInput
{
	float4 position : SV_POSITION;
	float4 depthPosition : POSITION0;
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

struct s_SkyMapOUTPUT
{
	float4 Pos : SV_POSITION;
	float3 TexCoord : TEXCOORD;
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

TextureCube SkyMap: register(t3);
SamplerState objSamplerState : register(s0); //WRAP

float3 SpotLight(PS_INPUT input, s_Light light);
float3 PointLight(PS_INPUT input, s_Light light);
float3 DirectLight(PS_INPUT input, s_Light light);

PS_INPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float3 normal : NORMAL, float3 tangent : TANGENT)
{
	PS_INPUT output;

	//inPos.w = 1;
	float4 inputPos = float4(inPos.xyz, 1.0f);
	output.Pos = mul(inputPos, WVP);
	output.WorldPos = mul(inputPos, World);
	output.Normal = mul(normal, World);
	output.Tangent = mul(tangent, World);
	output.TexCoord = inTexCoord;

	output.ViewPos = output.Pos;

	output.lightPos = Light[2].Pos.xyz - output.WorldPos.xyz;
	output.lightPos = normalize(output.lightPos);
	return output;
}

float4 PS(PS_INPUT input) : SV_TARGET
{
	input.Normal = normalize(input.Normal);


	float4 textDiffuse = Diffuse;
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
	
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	//clip(textDiffuse.w - 0.25f);
	float3 finalAmbient = textDiffuse * float3(0.3f, 0.3f, 0.3f);
	float3 lightColor = float3(0.0f, 0.0f, 0.0f);
	float3 shadowlightColor = float3(0.0f, 0.0f, 0.0f);
	
	
	float3 pointLight = PointLight(input, Light[0]);
	float3 DirLight = DirectLight(input, Light[1]);
	float3 spotLight1 = SpotLight(input, Light[2]);
	float3 spotLight2 = SpotLight(input, Light[3]);
	float3 spotLight3 = SpotLight(input, Light[4]);
	shadowlightColor = saturate(spotLight1);
	lightColor = saturate(spotLight3);
	finalColor = saturate(shadowlightColor + spotLight3 + finalAmbient);
	
	return float4(finalColor, textDiffuse.a);
}



s_SkyMapOUTPUT SkyBoxMap_VS(float3 inPos : POSITION)
{
	s_SkyMapOUTPUT output = (s_SkyMapOUTPUT)0;

	output.Pos = mul(float4(inPos, 1.0f), WVP).xyww;
	output.TexCoord = inPos;

	return output;
}

float4 SkyBoxMap_PS(s_SkyMapOUTPUT input) :SV_Target
{
	return SkyMap.Sample(objSamplerState, input.TexCoord);
}




float3 SpotLight(PS_INPUT input, s_Light light) :SV_Target
{
	//input.Normal = normalize(input.Normal);
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);

	float3 lightToPixel = light.Pos.xyz - input.WorldPos.xyz; // piexl -> light
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

float3 PointLight(PS_INPUT input, s_Light light) :SV_Target
{
	//input.Normal = normalize(input.Normal);
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 lightToPixel = light.Pos.xyz - input.WorldPos.xyz;
	float d = length(lightToPixel);

	lightToPixel /= d;

	float ratio = saturate(dot(lightToPixel, input.Normal));
	return ratio * light.Diffuse * light.Ambient / (light.Attenuation[0] + (light.Attenuation[1] * d) + (light.Attenuation[2] * (d * d)));

}

float3 DirectLight(PS_INPUT input, s_Light light) :SV_Target
{
	//input.Normal = normalize(input.Normal);
	float3 lightToPixel = -light.Dir;

	float ratio = saturate(dot(lightToPixel, input.Normal));
	return ratio * light.Diffuse * light.Ambient;


}

depthPSInput DepthVS(depthVSInput input : POSITION)
{
	depthPSInput output;

	float4 pos = float4(input.position, 1.0f);
	output.position = mul(pos, WVP);

	output.depthPosition = output.position;

	return output;
}


float4 DepthPS(depthPSInput input) : SV_TARGET
{
	float depthValue;
float4 color;

depthValue = input.depthPosition.z / input.depthPosition.w;

color = float4(depthValue, depthValue, depthValue, 1.0f);
return color;
}
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
Texture2D objShadowMap: register(t2); //cube
TextureCube SkyMap: register(t3);
Texture2D objShadowMap1: register(t4); //flash
Texture2D objShadowMap2: register(t5); //dog
SamplerState objSamplerState : register(s0); //WRAP
SamplerState objSamplerClamp : register(s1); //CLAMP

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
	float3 finalAmbient = textDiffuse * float3(0.46f, 0.46f, 0.46f);
	float3 flashlightColor = float3(0.0f, 0.0f, 0.0f);
	float3 spotlightColor = float3(0.0f, 0.0f, 0.0f);
	float3 spotlightColor1 = float3(0.0f, 0.0f, 0.0f);

	float2 projectTexCoord;
	float spotLightShadowValue;
	float spotLightShadowValue1;
	float flashlightShadowValue;

	// Calculate the projected texture coordinates(spotlight)
	projectTexCoord.x = ((input.ViewPos.x / input.ViewPos.w) / 2.0f) + 0.5f;
	projectTexCoord.y = -((input.ViewPos.y / input.ViewPos.w) / 2.0f) + 0.5f;

	spotLightShadowValue = objShadowMap.Sample(objSamplerClamp, projectTexCoord).r;

	flashlightShadowValue = objShadowMap1.Sample(objSamplerClamp, projectTexCoord).r;

	spotLightShadowValue1 = objShadowMap2.Sample(objSamplerClamp, projectTexCoord).r;


	float3 pointLight = PointLight(input, Light[0]);
	float3 DirLight = DirectLight(input, Light[1]);
	//float3 spotLight1 = float3(0.0f, 1.0f, 0.0f);
	float3 spotLight1 = SpotLight(input, Light[2]);
	float3 spotLight2 = SpotLight(input, Light[3]);
	float3 spotLight3 = SpotLight(input, Light[4]);
	spotlightColor = saturate(spotLight1) * spotLightShadowValue;

	spotlightColor1 = saturate(spotLight2) * spotLightShadowValue1;

	flashlightColor = saturate(spotLight3) * flashlightShadowValue;

	finalColor = saturate(spotlightColor + spotlightColor1 + flashlightColor + finalAmbient);

	return float4(finalColor, textDiffuse.a);
}

float3 SpotLight(PS_INPUT input, s_Light light) :SV_Target
{
	//input.Normal = normalize(input.Normal);
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 reflection;
	float4 specular;

	float3 lightToPixel = light.Pos.xyz - input.WorldPos.xyz; // piexl -> light
	float d = length(lightToPixel);
	float temp = 1.0f;
	if (d > 10)
		temp = 10 / d;

	lightToPixel /= d;

	float surfaceRatio = saturate(dot(-lightToPixel, normalize(light.Dir)));
	float3 spotFactor = pow(max(surfaceRatio, 0.0f),light.Cone);
	float lightRatio = saturate(dot(normalize(lightToPixel), input.Normal));

	if (lightRatio > 0.0f)
	{
		finalColor = temp * spotFactor * lightRatio * light.Diffuse  * light.Ambient / (light.Attenuation[0] + (light.Attenuation[1] * d) + (light.Attenuation[2] * (d * d)));


	}

	return finalColor;


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


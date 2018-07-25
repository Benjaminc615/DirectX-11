cbuffer MatrixBuffer
{
	float4x4 WVP;
	float4x4 worldMatrix;
	float4x4 viewMatrix;
	float4x4 projectMatrix;
	float4x4 lightViewMatrix;
	float4x4 lightProjectMatrix;
};

cbuffer LightBuffer
{
	float3 lightPos;
	float padding;
};

struct VertexInput
{
	float4 position : POSITION;
	float3 normal	: NORMAL;
};



struct PixelInput
{
	float4 position : SV_POSITION;
	float3 normal	: NORMAL;
	float4 lightViewPos : TEXCOORD1;
	float3 lightPos : TEXCOORD2;
};

Texture2D depthMapTexture;
SamplerState sampleClamp;

PixelInput BlackWhiteShadowVS(VertexInput input)
{
	PixelInput output;
	float4 worldPos;

	input.position.w = 1;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectMatrix);
	output.lightViewPos = mul(input.position, worldMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightViewMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightProjectMatrix);

	output.normal = normalize(mul(input.normal, worldMatrix));

	worldPos = mul(input.position, worldMatrix);
	output.lightPos =normalize(lightPos.xyz - worldPos.xyz);
	

	return output;
}

float4 BlackWhiteShadowPS(PixelInput input) : SV_TARGET
{
	float4 color;
	float2 projectTexCoord;
	float bias;
	float depthValue;
	float lightDepthValue;

	bias = 0.001f;
	color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	projectTexCoord.x = ((input.lightViewPos.x / input.lightViewPos.w) / 2.0f) + 0.5f;
	projectTexCoord.y = -((input.lightViewPos.y / input.lightViewPos.w) / 2.0f) + 0.5f;

	if ((saturate(projectTexCoord.x) == projectTexCoord.x)  && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		depthValue = depthMapTexture.Sample(sampleClamp, projectTexCoord).r;
		lightDepthValue = input.lightViewPos.z / input.lightViewPos.w;
		lightDepthValue = lightDepthValue - bias;

		if (lightDepthValue < depthValue)
		{
			if (saturate(dot(input.normal, input.lightPos)) > 0.0f)
			{
				color = float4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	return color;
}
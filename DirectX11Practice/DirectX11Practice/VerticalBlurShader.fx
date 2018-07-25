cbuffer MatrixBuffer
{
	float4x4 WVP;
};

cbuffer ScreenSizeBuffer
{
	float screenHeight;
	float3 padding;
};

struct VertexInput
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 texCoord	: TEXCOORD;
	float2 texCoord1 : TEXCOORD1;
	float2 texCoord2 : TEXCOORD2;
	float2 texCoord3 : TEXCOORD3;
	float2 texCoord4 : TEXCOORD4;
	float2 texCoord5 : TEXCOORD5;
	float2 texCoord6 : TEXCOORD6;
	float2 texCoord7 : TEXCOORD7;
	float2 texCoord8 : TEXCOORD8;
	float2 texCoord9 : TEXCOORD9;
};

Texture2D shaderTexture;
SamplerState SampleType;

PixelInput VerticalBlurVS(VertexInput input)
{
	PixelInput output;
	float texelSize;

	input.position.w = 1.0;

	output.position = mul(input.position, WVP);

	output.texCoord = input.texCoord;
	texelSize = 1 / screenHeight;

	output.texCoord1 = saturate(input.texCoord + float2(0.0f, texelSize * -4.0f));
	output.texCoord2 = saturate(input.texCoord + float2(0.0f, texelSize * -3.0f));
	output.texCoord3 = saturate(input.texCoord + float2(0.0f, texelSize * -2.0f));
	output.texCoord4 = saturate(input.texCoord + float2(0.0f, texelSize * -1.0f));
	output.texCoord5 = saturate(input.texCoord + float2(0.0f, texelSize *  0.0f));
	output.texCoord6 = saturate(input.texCoord + float2(0.0f, texelSize *  1.0f));
	output.texCoord7 = saturate(input.texCoord + float2(0.0f, texelSize *  2.0f));
	output.texCoord8 = saturate(input.texCoord + float2(0.0f, texelSize *  3.0f));
	output.texCoord9 = saturate(input.texCoord + float2(0.0f, texelSize *  4.0f));

	return output;
}

float4 VerticalBlurPS(PixelInput input) : SV_TARGET
{
	float weight0, weight1, weight2, weight3, weight4;
	float normalization;
	float4 color;

	weight0 = 1.0f;
	weight1 = 0.9f;
	weight2 = 0.55f;
	weight3 = 0.18f;
	weight4 = 0.1f;

	normalization = weight0 + 2.0f * (weight1 + weight2 + weight3 + weight4);

	weight0 /= normalization;
	weight1 /= normalization;
	weight2 /= normalization;
	weight3 /= normalization;
	weight4 /= normalization;

	color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color += shaderTexture.Sample(SampleType, input.texCoord1)* weight4;
	color += shaderTexture.Sample(SampleType, input.texCoord2)* weight3;
	color += shaderTexture.Sample(SampleType, input.texCoord3)* weight2;
	color += shaderTexture.Sample(SampleType, input.texCoord4)* weight1;
	color += shaderTexture.Sample(SampleType, input.texCoord5)* weight0;
	color += shaderTexture.Sample(SampleType, input.texCoord6)* weight1;
	color += shaderTexture.Sample(SampleType, input.texCoord7)* weight2;
	color += shaderTexture.Sample(SampleType, input.texCoord8)* weight3;
	color += shaderTexture.Sample(SampleType, input.texCoord9)* weight4;
	color.w = 1.0f;

	return color;
}
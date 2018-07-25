cbuffer	matrixBuffer
{
	float4x4 WVP;
};

struct VertexInput
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

Texture2D shaderTexture;
SamplerState SampleWrap;

PixelInput TextureVS(VertexInput input)
{
	PixelInput output;
	input.position.w = 1.0f;
	output.position = mul(input.position, WVP);
	output.texCoord = input.texCoord;

	return output;
}

float4 TexturePS(PixelInput input) :SV_TARGET
{
	float4 color;
	color = shaderTexture.Sample(SampleWrap, input.texCoord);
	return color;
}
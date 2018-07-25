struct VertexInput
{
	float4 pos : POSITION;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
};

cbuffer MatrixBuffer
{
	matrix WVP;
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectMatrix;
};

PixelInput DebuggingLineVS(VertexInput input : POSITION)
{
	PixelInput output;
	input.pos.w = 1.0f;
	output.pos = mul(input.pos, WVP);

	return output;
}

float4 DebuggingLinePS(PixelInput input) : SV_TARGET
{
	float4 color = float4(0.0f, 1.0f, 0.0f, 1.0f);

	//depthValue = input.depthPos.z / input.depthPos.w;
	//color = float4(depthValue, depthValue, depthValue, 1.0f);

	return color;
}

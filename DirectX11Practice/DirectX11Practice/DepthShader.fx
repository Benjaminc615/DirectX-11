struct VertexInput
{
	float4 pos : POSITION;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 depthPos : TEXTURE0;
};

cbuffer MatrixBuffer
{
	matrix WVP;
};

PixelInput DepthVS(VertexInput input : POSITION)
{
	PixelInput output;
	input.pos.w = 1.0f;
	output.pos = mul(input.pos, WVP);
	output.depthPos = output.pos;

	return output;
}

float4 DepthPS(PixelInput input) : SV_TARGET
{
	float depthValue;
	float4 color;

	depthValue = input.depthPos.z / input.depthPos.w;
	color = float4(depthValue, depthValue, depthValue, 1.0f);

	return color;
}

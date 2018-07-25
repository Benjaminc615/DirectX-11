struct PSInput
{
	float4 Pos : SV_POSITION;
	float3 TexCoord : TEXCOORD;
};

cbuffer MatrixBuffer
{
	float4x4 WVP;
};

TextureCube SkyMap: register(t3);
SamplerState objSamplerState : register(s0); //WRAP

PSInput SkyBoxVS(float3 inPos : POSITION)
{
	PSInput output = (PSInput)0;

	output.Pos = mul(float4(inPos, 1.0f), WVP).xyww;
	output.TexCoord = inPos;

	return output;
}

float4 SkyBoxPS(PSInput input) :SV_Target
{
	return SkyMap.Sample(objSamplerState, input.TexCoord);
}

struct VS_IN
{
	float3 p : POSITION; 
    float4 c : COLOR;
	float2 t : TEXTURE;
};
struct VS_OUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
VS_OUT VS(VS_IN input) 
{
	VS_OUT output = (VS_OUT)0;
	output.p = float4(input.p,1.0f);
	output.c = input.c;
	output.t = input.t;
	return output;
}

Texture2D    g_txTex			: register(t0);
SamplerState g_SampleWrap		: register(s0);

float4 PS(VS_OUT input) : SV_Target
{
	float4 vColor = g_txTex.Sample(g_SampleWrap , input.t);
	return vColor;
}
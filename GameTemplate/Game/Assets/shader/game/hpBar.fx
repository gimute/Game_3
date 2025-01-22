//HPバー用のシェーダー

cbuffer cb : register(b0){
	float4x4 mvp;
	float4 mulColor;
};

cbuffer parameterCb : register(b1)
{
    float3 parameter;
};

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    float test = max( 0.0f, 1.0f - parameter.z / 100.0f );
	
    float wipeSize = parameter.x * test;
	
    float pos = 1600.0f - In.pos.x;
	
    clip(pos - wipeSize);
	
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}
/*!
 * @brief �u���[��
 */

cbuffer cb : register(b0)
{
    float4x4 mvp; // MVP�s��
    float4 mulColor; // ��Z�J���[
}

struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};


PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

Texture2D<float4> mainRenderTargetTexture : register(t0); // ���C�������_�����O�^�[�Q�b�g
sampler Sampler : register(s0);

//�P�x���o�p�̃s�N�Z���V�F�[�_�[
float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
    //���C�������_�����O�^�[�Q�b�g����J���[���T���v�����O
    float4 color = mainRenderTargetTexture.Sample(Sampler, In.uv);
    
    //�T���v�����O�����J���[�̖��邳���v�Z
    float t = dot(color.xyz, float3(0.2125f, 0.7154, 0.0721f));
    
    //�J���[�̖��邳��1�ȉ��Ȃ�s�N�Z���L��
    clip(t - 1.0f);
  
    return color;
}



// 4���̃{�P�P�x�摜
Texture2D<float4> g_bokeTexture_0 : register(t0);
Texture2D<float4> g_bokeTexture_1 : register(t1);
Texture2D<float4> g_bokeTexture_2 : register(t2);
Texture2D<float4> g_bokeTexture_3 : register(t3);

//�ŏI�I�ȃu���[�������s�N�Z���V�F�[�_�[
float4 PSBloomFinal(PSInput In) : SV_Target0
{
    //�{�P�摜���T���v�����O���āA���ς�����ďo�͂���
    float4 combineColor = g_bokeTexture_0.Sample(Sampler, In.uv);
    combineColor += g_bokeTexture_1.Sample(Sampler, In.uv);
    combineColor += g_bokeTexture_2.Sample(Sampler, In.uv);
    combineColor += g_bokeTexture_3.Sample(Sampler, In.uv);
    combineColor /= 4.0f;
    combineColor.a = 1.0f;
    
    return combineColor;
}
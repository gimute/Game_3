//��������O���Ɍ����u���[

cbuffer cb : register(b0)
{
    float4x4 mvp;       //MVP�s��
    float4 mulColor;    //��Z�J���[
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

Texture2D<float4> sceneTexture : register(t0); // �V�[���e�N�X�`��
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

float4 PSMain(PSInput In) : SV_Target0
{
    //�s�N�Z���̃J���[���擾
    float4 color = sceneTexture.Sample(Sampler, In.uv);

    //�������猻�݌v�Z���̃s�N�Z����uv�ɐL�т�x�N�g��
    float2 centerToInUVVec;
    centerToInUVVec.x = (0.5f - In.uv.x);
    centerToInUVVec.y = (0.5f - In.uv.y);
    
    //��ʂ̒����̓u���[�������[�ɍs���قǃu���[�����߂銴���ɂ������̂ŁA
    //lerp�p�Ƀx�N�g���̒����ɂ���ĕϓ�����l��p�ӂ���
    float t = ((centerToInUVVec.x * centerToInUVVec.x) + (centerToInUVVec.y * centerToInUVVec.y)) / 0.5f;
    
    //���K��
    //�����ł�����ƕϐ��̈Ӗ����ς���Ă邩��ϐ����ς����ق����ǂ�����?
    normalize(centerToInUVVec);
    //�K���ɏ���������
    centerToInUVVec /= 20.0f;
    
    //������x�N�g�������̃s�N�Z�����T���v�����O
    float4 blurColor;
    blurColor = sceneTexture.Sample(Sampler, In.uv + centerToInUVVec);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 2);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 3);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 4);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 5);
    
    
    
    //��e�N�Z���ƃT���v�����O����5�e�N�Z���̕��ςȂ̂�6�ŏ��Z����
    //color = blurColor + color;
    //color /= 6.0f;
    
    
    blurColor /= 5.0f;
    color = lerp(color, blurColor, t);
    
    
    return color;
}
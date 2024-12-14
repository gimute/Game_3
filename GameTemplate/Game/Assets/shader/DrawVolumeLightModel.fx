///////////////////////////////////////
//�{�����[�����C�g���f���`��V�F�[�_�[
///////////////////////////////////////

//�V�[���̐[�x�Ńe�N�X�`��
Texture2D <float4>g_sceneDepthTexture : register(t10);
//�T���v���[
sampler Sampler : register(s0);

///////////////////////////////////////
//�\����
///////////////////////////////////////

//�s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos : SV_Position;
    float4 posInProj : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
};

///////////////////////////////////////
// �萔�o�b�t�@�B
///////////////////////////////////////
// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};


SPSIn VSMain(float4 pos : POSITION)
{
    SPSIn psIn;
    psIn.pos = mul(mWorld, pos);    //���f���̒��_�����[���h���W�n�ɕϊ�
    //���_�V�F�[�_�[���烏�[���h���W���o��
    psIn.worldPos = pos;
    psIn.pos = mul(mView, psIn.pos);    //���f���̒��_�����[���h���W�n�ɕϊ�
    psIn.pos = mul(mProj, psIn.pos);    //�J�������W�n����X�N���[�����W�n�ɕϊ�
    psIn.posInProj = psIn.pos;
    
    return psIn;
}

/// <summary>
/// �������ސ[�x�l���v�Z����B
/// </summary>
float CalcDrawDepth(SPSIn psIn)
{
    
    float2 uv = psIn.posInProj.xy / psIn.posInProj.w;
    uv = uv * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);
    float sceneDepth = g_sceneDepthTexture.Sample(Sampler, uv).r;
    float z = min(sceneDepth, psIn.pos.z);
    
    return z;
}

/// <summary>
/// �O��/�w�ʕ`��p�̃s�N�Z���V�F�[�_�[�G���g���[�֐��B
/// </summary>
float4 PSMainFrontBackModel(SPSIn psIn) : SV_Target0
{
    //�{�����[�����C�g�}�b�v�ɏ������ސ[�x�l���v�Z����
    float z = CalcDrawDepth(psIn);
    return float4(z, z, z, z);
}

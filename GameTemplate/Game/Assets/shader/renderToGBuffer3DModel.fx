/*!
 * @brief G-Buffer�ւ̕`��
 */

// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

//�X�L�j���O�p�̒��_�f�[�^���ЂƂ܂Ƃ߁B
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

// ���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    
    SSkinVSIn skinVert; //�X�L���p�̃f�[�^�B
};

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
};

// �s�N�Z���V�F�[�_�[����̏o��
struct SPSOut
{
    float4 albedo : SV_Target0; // �A���x�h
    float4 normal : SV_Target1; // �@��
    float depth : SV_Target2;   //�[�x�l
};

// ���f���e�N�X�`��
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //�{�[���s��B
// �T���v���[�X�e�[�g
sampler g_sampler : register(s0);

/// <summary>
//�X�L���s����v�Z����B
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// ���f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;

    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    
    psIn.pos = mul(m, vsIn.pos); // 1. ���f���̒��_�����[���h���W�n�ɕϊ�
    psIn.pos = mul(mView, psIn.pos); // 2. ���[���h���W�n����J�������W�n�ɕϊ�
    psIn.pos = mul(mProj, psIn.pos); // 3. �J�������W�n����X�N���[�����W�n�ɕϊ�
    psIn.normal = normalize(mul(m, vsIn.normal));
    psIn.uv = vsIn.uv;
    
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));

    return psIn;
}

/// <summary>
/// �X�L���Ȃ����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// �X�L�����胁�b�V���̒��_�V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// ���f���p�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
/// </summary>
SPSOut PSMain(SPSIn psIn)
{
    // step-6 G-Buffer�ɏo��
    SPSOut psOut;
    
    //�A���x�h�J���[���o��
    psOut.albedo = g_texture.Sample(g_sampler, psIn.uv);
    
    //�@���}�b�v����^���W�F���g�X�y�[�X�̖@�����T���v�����O
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    
    //�^���W�F���g�X�y�[�X�̖@������0�`1�͈̔͂���-1�`1�͈̔͂ɕ�������
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    float3 normal = psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + psIn.normal * localNormal.z;
    
    //�@���o��
    //�o�͂�0�`1�Ɋۂ߂��Ă��܂��̂Ń}�C�i�X�̒l�������Ă��܂�
    //�Ȃ̂�-1�`1��0�`1�ɕϊ�����
    //(-1~1) / 2.0 = (-0.5~0.5)
    //(-0.5~0.5) + 0.5 = (0.0~1.0)
    psOut.normal.xyz = (normal / 2.0f) + 0.5f;
    //�X�y�L�������x��normal.w�ɑ��
    psOut.normal.w = g_specularMap.Sample(g_sampler, psIn.uv).r;
    //psOut.normal = (psIn.normal / 2.0f) + 0.5f;
    
    //�[�x�l���o��
    psOut.depth = psIn.pos.z;
    
    return psOut;
}

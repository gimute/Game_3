///////////////////////////////////////
//�{�����[�����C�g�`��V�F�[�_�[
///////////////////////////////////////

//�T���v���[
sampler Sampler : register(s0);

///////////////////////////////////////
// �\����
///////////////////////////////////////

//�|�C���g���C�g
struct PointLight
{
    float3 position; //���W
    int isUse; //�g�p���t���O
    float3 color; //���C�g�̃J���[
    float range; //�e���͈�
    float3 posintionInView; //�J������Ԃł̍��W
    int pow; //�e�����̗ݏ搔
};

//�X�|�b�g���C�g
struct SpotLight
{
    float3 position; //���W
    int isUse; //�g�p���t���O
    float3 color; //���C�g�̃J���[
    float range; //�e���͈�
    float3 direction; //�ˏo����
    float angle; //�ˏo�͈�
    float3 positionInView; //�J������Ԃł̍��W
    float rangePow; //�����ɂ��e�����̗ݏ搔
    float3 directionInView; // �J������Ԃł̎ˏo�����B
    float anglePow; //�p�x�ɂ��e�����̗ݏ搔
};

///////////////////////////////////////
// �萔�o�b�t�@�B
///////////////////////////////////////

cbuffer cb : register(b0)
{
    float4x4 mvp; 
    float4 mulColor;
};

//�|�C���g���C�g�p�̒萔�o�b�t�@�[
cbuffer finalPointLightCb : register(b1)
{
    PointLight pointLight; //�X�|�b�g���C�g
    float4x4 ptLig_mViewProjInv; //�r���[�v���W�F�N�V�����s��̋t�s��
    float ptLig_randomSeed; //�����_���V�[�h
}

//�X�|�b�g���C�g�p�̒萔�o�b�t�@�[
cbuffer finalSpotLightCb : register(b1)
{
    SpotLight spotLight;    //�X�|�b�g���C�g
    float4x4 spLig_mViewProjInv;  //�r���[�v���W�F�N�V�����s��̋t�s��
    float spLig_randomSeed; //�����_���V�[�h
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

Texture2D<float4> albedoTexture : register(t0); // �A���x�h�J���[
Texture2D<float4> g_volumeLightMapFront : register(t1);
Texture2D<float4> g_volumeLightMapBack : register(t2);

PSInput VSFinal(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    return psIn;
}

float GetRandomNumber(float2 texCoord, float Seed)
{
    return frac(sin(dot(texCoord.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}


float3 CalcWorldPosFromUVZ(float2 uv, float zInScreen, float4x4 mViewProjInv)
{
    float3 screenPos;
    screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2(-1.0f, 1.0f);
    screenPos.z = zInScreen;
    
    float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
    worldPos.xyz /= worldPos.w;
    return worldPos.xyz;
}

float4 PSFinal_SpotLight(PSInput In) : SV_Target0
{
    float3 lig = 0;
    float2 uv = In.uv;
    
    //�{�����[�����C�g�̐[�x�l���󂯎��
    float volumeFrontZ = g_volumeLightMapFront.Sample(Sampler, uv).r;
    float volumeBackZ = g_volumeLightMapBack.Sample(Sampler, uv).r;
    
    //�{�����[�����C�g�̐[�x�l���烏�[���h���W�𕜌�����
    float3 volumePosBack = CalcWorldPosFromUVZ(uv, volumeBackZ, spLig_mViewProjInv);
    float3 volumePosFront = CalcWorldPosFromUVZ(uv, volumeFrontZ, spLig_mViewProjInv);
    
    float t0 = dot(spotLight.direction, volumePosFront - spotLight.position);
    float t1 = dot(spotLight.direction, volumePosBack - spotLight.position);
    float t = t0 / (t0 + t1);
    //�{�����[�����C�g�̒��S?
    float3 volumeCenterPos = lerp(volumePosFront, volumePosBack, t);
    float volume = length(volumePosBack - volumePosFront);
    
    //�{�����[���������ӏ��̓s�N�Z���L��
    clip(volume - 0.001f);
    
    //�s�N�Z���̃J���[���擾
    float4 albedoColor = albedoTexture.Sample(Sampler, uv);
    
    //�����ɂ����̉e�������v�Z
    float3 ligDir = (volumeCenterPos - spotLight.position);
    float distance = length(ligDir);
    ligDir = normalize(ligDir);
    float3 affectBase = 1.0f - min(1.0f, distance / spotLight.range);
    float3 affect = pow(affectBase, spotLight.rangePow);

    //�����Ċp�x�ɂ�錸�����v�Z����
    //�p�x�ɔ�Ⴕ�ď������Ȃ��Ă����e�������v�Z����
    float angleLigToPixel = saturate(dot(ligDir, spotLight.direction));
    
    //dot()�ŋ��߂��l��acos()�ɓn���Ċp�x�����߂�
    angleLigToPixel = abs(acos(angleLigToPixel));
    
    //�p�x�ɂ�錸�����v�Z
    float3 angleAffectBase = max(0.0f, 1.0f - 1.0f / spotLight.angle * angleLigToPixel);
    angleAffectBase = min(1.0f, angleAffectBase * 1.8f);
    float3 angleAffect = pow(angleAffectBase, spotLight.anglePow);
    affect *= angleAffect;
    
    //�O�̌�������
    //���̃x�[�X���v�Z
    float3 ligBase = albedoColor * step(volumeFrontZ, albedoColor.w) * max(0.0f, log(volume)) * 0.1f;
    //���̃x�[�X�ɉe��������Z����
    lig = ligBase * affect * spotLight.color;
    lig += ligBase * affect.y * spotLight.color;
    lig += ligBase * affect.z * spotLight.color;
    
    // ��C���̃`���̕\���Ƃ��ăm�C�Y��������B
    lig *= lerp(0.9f, 1.1f, GetRandomNumber(uv, spLig_randomSeed));

    return float4(lig, 1.0f);
}

float4 PSFinal_PointLight(PSInput In) : SV_Target0
{
    float3 lig = 0;
    float2 uv = In.uv;
	
    float volumeFrontZ = g_volumeLightMapFront.Sample(Sampler, uv).r;
    float volumeBackZ = g_volumeLightMapBack.Sample(Sampler, uv).r;
  
    float3 volumePosBack = CalcWorldPosFromUVZ(uv, volumeBackZ, ptLig_mViewProjInv);
    float3 volumePosFront = CalcWorldPosFromUVZ(uv, volumeFrontZ, ptLig_mViewProjInv);
    

    
    float3 volumeCenterPos = (volumePosFront + volumePosBack) * 0.5f;
    float volume = length(volumePosBack - volumePosFront);

    // �{�����[�����Ȃ��ӏ��̓s�N�Z���L���B
    clip(volume - 0.001f);

    float4 albedoColor = albedoTexture.Sample(Sampler, uv);
    
    // �����ɂ�錸���B
    float3 ligDir = (volumeCenterPos - pointLight.position);
    float distance = length(ligDir);
    ligDir = normalize(ligDir);
    float affect = pow(1.0f - min(1.0f, distance / pointLight.range), pointLight.pow);

    lig = albedoColor * pointLight.color * affect * step(volumeFrontZ, albedoColor.w) * max(0.0f, log(volume)) * 0.05f;
    lig *= lerp(0.9f, 1.1f, GetRandomNumber(uv, ptLig_randomSeed));
    return float4(lig, 1.0f);
}
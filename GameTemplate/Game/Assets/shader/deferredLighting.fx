///////////////////////////////////////////////////////////
//�萔
///////////////////////////////////////////////////////////
static const int MAX_POINT_LIGHT = 250; // �|�C���g���C�g�̍ő吔
static const int MAX_SPOT_LIGHT = 250; // �X�|�b�g���C�g�̍ő吔

// ��x�Ɏ��s�����X���b�h��
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

///////////////////////////////////////////////////////////
//�\����
///////////////////////////////////////////////////////////
// �f�B���N�V�������C�g
struct DirectionalLight
{
    float3 direction; //���C�g�̕���
    int castShadow; //�e���L���X�g���邩�H
    float3 color; //���C�g�̃J���[
    
};

//�|�C���g���C�g
struct PointLight
{
    float3 position;    //���W
    int isUse;          //�g�p���t���O
    float3 color;       //���C�g�̃J���[
    float range;        //�e���͈�
    float3 posintionInView; //�J������Ԃł̍��W
    int pow;            //�e�����̗ݏ搔
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

///////////////////////////////////////////////////////////
//�萔�o�b�t�@�[
///////////////////////////////////////////////////////////
cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
    float4 screenParam;
};

cbuffer LightCb : register(b1)
{
    //���C�g���
    DirectionalLight directionalLight;  //�f�B���N�V�������C�g
    PointLight pointLights[MAX_POINT_LIGHT]; //�|�C���g���C�g�̔z��
    SpotLight spotLights[MAX_SPOT_LIGHT];   //�X�|�b�g���C�g�̔z��
    float3 eyePos;                      //���_
    int numPointLight;                  //�|�C���g���C�g�̐�
    float3 ambientLig;                     //����
    int numSpotLight;                   //�X�|�b�g���C�g�̐�
    float3 eyeDir;      //�����̕���
    
    //���̑�
    float4x4 mViewProjInv;  //�Q�[���J�����̃r���[�v���W�F�N�V�����s��̋t�s��
    
    float4x4 mlvp;  //�V���h�E�p���C�g�J�����̃r���[�v���W�F�N�V�����s��
    
    float3 ligCameraPos;    //�V���h�E�}�b�v�p�̃��C�g�J�����̃|�W�V����

};

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

Texture2D<float4> albedoTexture : register(t0); // �A���x�h
Texture2D<float4> normalTexture : register(t1); // �@��
Texture2D<float> deothTexture : register(t2);   // �ˉe��Ԃɐ��K�����ꂽ�[�x�l
Texture2D<float4> g_shadowMap : register(t3);  //�V���h�E�}�b�v

// �^�C�����Ƃ̃|�C���g���C�g�̃C���f�b�N�X�̃��X�g
StructuredBuffer<uint> pointLightListInTile : register(t20);
StructuredBuffer<uint> spotLightListInTile : register(t21);


sampler Sampler : register(s0);
///////////////////////////////////////////////////////////
//�֐��錾
///////////////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal);
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower);
float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normal);
float3 CalcLighting(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower); //���C�g�̋��ʏ���
float3 CalcLigFromDirectionLight(float3 normal, float3 worldPos, float specPower);
float3 CalcLigFromPointLight(float3 normal, float3 worldPos, float specPower, uint tileIndex);
float3 CalcLigFromSpotLight(float3 normal, float3 worldPos, float specPower, uint tileIndex);
//UV���W�Ɛ[�x�l���烏�[���h���W���v�Z����
float3 CalcWorldPosFromUVZ(float2 uv, float zInProjectionSpace, float4x4 mViewProjInv)
{
    float3 screenPos;
    screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2(-1.0f, 1.0f);
    screenPos.z = zInProjectionSpace;

    float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
    worldPos.xyz /= worldPos.w;
    return worldPos.xyz;
}

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    return psIn;
}

//�s�N�Z���V�F�[�_�̃G���g���[�֐�
float4 PSMain(PSInput In) : SV_Target0
{
    //TBR�p�̏���
    //���̃s�N�Z�����܂܂�Ă���^�C���̔ԍ����v�Z����
    //�X�N���[�����^�C���ŕ����������̃Z����X���W�����߂�
    uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
    
    //�^�C���C���f�b�N�X���v�Z����
    uint tileIndex = floor(In.pos.x / TILE_WIDTH)
                   + floor(In.pos.y / TILE_HEIGHT) * numCellX;
    
    
    ////////////////////////////////////////////////////////////
    
    
    // G-Buffer�̓��e���T���v�����O
    float4 albedo = albedoTexture.Sample(Sampler, In.uv);
    float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
    float specPower = normalTexture.Sample(Sampler, In.uv).w;
    
    //�@����(0~1)����(-1~1)�ɕ������Ă���ۂ�
    normal = (normal * 2.0) - 1.0f;
    //������1���z���Ȃ��悤�ɐ��K��
    normal = normalize(normal);
    
    float z = deothTexture.Sample(Sampler, In.uv);
    
    //�ˉe��Ԃ̐[�x�l���烏�[���h���W�𕜌�����
    float3 worldPos = CalcWorldPosFromUVZ(In.uv, z, mViewProjInv);
    
    
    //�f�B���N�V�������C�g�ɂ��������߂�
    float3 directionLight = CalcLigFromDirectionLight(normal, worldPos, specPower);
    //�|�C���g���C�g�ɂ��������߂�
    float3 pointLight = CalcLigFromPointLight(normal, worldPos, specPower, tileIndex);
    //�X�|�b�g���C�g�ɂ��������߂�
    float3 spotLight = CalcLigFromSpotLight(normal, worldPos, specPower, tileIndex);
    
    //���߂����C�g�̌��Ɗ�����S�đ����čŏI�I�Ȍ������߂�
    float3 finalLig = directionLight + pointLight + spotLight + ambientLig;
    
    //�V���h�E�C���O
    //���C�g���猩�����W���o��
    float4 posInLVP = mul(mlvp, float4(worldPos, 1.0f));
    
    //UV��Ԃɍ��W�ϊ�
    //���C�g���猩�����W�𐳋K���X�N���[�����W�n�ɂ�
    float2 shadowMapUV = posInLVP.xy / posInLVP.w;
    //���オ-1.0f,1.0f����
    //���オ0.0f,0.0f�ɂȂ�悤�ɂ��āAUV��ԂɕύX
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;   

    //�V���h�E�}�b�v�͈͓̔����ǂ�������
    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {
        //�V���h�E�}�b�v����l���T���v�����O
        float2 shadowValue = g_shadowMap.Sample(Sampler, shadowMapUV).xy;
        
        //�s�N�Z�����烉�C�g�̋������v�Z����
        float zInLVP = length(worldPos.xyz - ligCameraPos) / 1000.0f;
        
        //���̃s�N�Z�����Օ�����Ă��邩���ׂ�
        if(zInLVP > shadowValue.r && zInLVP <= 1.0f)
        {            
            //�`�F�r�V�F�t�̕s�����𗘗p���Č���������m�������߂�
            
            float depth_sq = shadowValue.x * shadowValue.x;
            
            //���̃O���[�v�̕��U������߂�
            //���U���傫���قǁAvariance�̐��l�͑傫���Ȃ�
            float variance = min(shadowValue.y - depth_sq, 0.0001f);
            
            //���̃s�N�Z�����C�g���猩���[�x�l�ƃV���h�E�}�b�v�̕��ς̐[�x�l�̍������߂�
            float md = zInLVP - shadowValue.x;

            //�����͂��m�������߂�
            float lit_factor = variance / (variance + md * md);
            
            //������f�B���N�V�������C�g�̌��𔽎˂��Ȃ��ʂ͌����͂��m�����������ĉe����߂�
            float t = max(0.0f, dot(normal, directionalLight.direction) * -1.0f);
            lit_factor = min(1.0f, lit_factor + (1 - t));
            
            //�V���h�E�J���[�����߂�
            float3 shadowColor = albedo.xyz * 0.5f;
            
            //����������m�����g���Ēʏ�J���[�ƃV���h�E�J���[����`���
            albedo.xyz = lerp(shadowColor, albedo.xyz, lit_factor);
        }
        
    }
    
    //�ŏI�I�ȏo�̓J���[�����߂�
    //�s�N�Z���̐F���󂯎��
    float4 finalColor = albedo;
    //���߂��ŏI�I�Ȍ�����Z����
    finalColor.xyz *= finalLig;
    
    //���߂��ŏI�J���[��Ԃ�
    return finalColor;
}

///////////////////////////////////////////////////////////
//�֐���`
///////////////////////////////////////////////////////////

//Lambert�g�U���ˌ��̌v�Z
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal)
{   
    float t = max(0.0f, dot(normal, ligDir) * -1.0f);

    return ligColor * t;
}

//Phonng���ʔ��ˌ��̌v�Z
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower)
{
    float3 toEye = normalize(eyePos - worldPos);
    
    float3 r = reflect(ligDir, normal);
    
    float t = max(0.0f, dot(toEye, r));
    
    t = pow(t, 5.0f);
    
    return ligColor * t * specPower;
}

//�������C�g
float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normal)
{
    //�������C�g�̋��������߂�
    float power1 = 1.0f - max(0.0f, min(dot(ligDir, normal), 1.0f));
    
    //�J�����̌����𐳋K�����Ă��x�N�g���̑傫����1���z���邱�Ƃ�����
    //�`�悪�o�O��̂�min�֐���1���z���Ȃ��悤�ɂ���
    float power2 = 1.0f - max(0.0f, min(dot(eyeDir, normal) * -1.0f, 1.0f));
 
    float limPower = power1 * power2;
    //�����̕ω����w���֐��I�ɂ���
    limPower = pow(limPower, 1.3);
    
    //�������C�g�̃J���[���v�Z���ĕԂ�
    //�Ȃ񂩃������C�g����������̂�0.5�{�ɂ���
    return ligColor * limPower * 0.5f;
}

//���C�g�̋��ʏ���
float3 CalcLighting(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower)
{
    //�g�U���˂����߂�
    float3 diffLig = CalcLambertDiffuse(ligDir, ligColor, normal);
    //���ʔ��˂����߂�
    float3 phongLig = CalcPhongSpecular(ligDir, ligColor, normal, worldPos, specPower);
    //�������C�g�����߂�
    float3 limLig = CalcLimLight(ligDir, ligColor, normal);
    
    //���߂����C�g�̌���S�đ����ĕԂ�
    return diffLig + phongLig + limLig;
}

//�f�B���N�V�������C�g�ɂ�锽�ˌ��v�Z
float3 CalcLigFromDirectionLight(float3 normal, float3 worldPos, float specPower)
{
    //���C�e�B���O�̌v�Z
    float3 lig = CalcLighting(directionalLight.direction, directionalLight.color, normal, worldPos, specPower);
    
    //return diffLig;
    //return phongLig;
    //return limLig;
    
    //�ŏI�I�Ȍ���Ԃ�
    return lig;
}

//�|�C���g���C�g�ɂ�锽�ˌ��v�Z
float3 CalcLigFromPointLight(float3 normal, float3 worldPos, float specPower, uint tileIndex)
{
    //�S�Ẵ|�C���g���C�g�̌��ʂ𑫂����ŏI�I�ȃ��C�g
    float3 finalLig = { 0.0f, 0.0f, 0.0f };
 
    //�܂܂��^�C���̉e���̊J�n�ʒu�ƏI���ʒu���v�Z����
    uint lightStart = tileIndex * numPointLight;
    uint lightEnd = lightStart + numPointLight;
    
    //�^�C���C���f�b�N�X���v�Z����
    for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++)
    {
        uint ligNo = pointLightListInTile[lightListIndex];
        if (ligNo == 0xffffffff)
        {
            //���̃^�C���Ɋ܂܂��|�C���g���C�g�͂����Ȃ�
            break;
        }
        
        //�g�U���˂��v�Z
        //1.��������T�[�t�F�C�X�ɓ��˂���x�N�g�����v�Z
        float3 ligDir = normalize(worldPos - pointLights[ligNo].position);
        //2.��������T�[�t�F�C�X�܂ł̋������v�Z
        float distance = length(worldPos - pointLights[ligNo].position);
            
        //���C�e�B���O�̌v�Z
        float3 lig = CalcLighting(ligDir, pointLights[ligNo].color, normal, worldPos, specPower);
            
        //�����ɔ�Ⴕ�ď������Ȃ��Ă����e�������v�Z����
        float affect = 1.0f - min(1.0f, distance / pointLights[ligNo].range);
        //�e������ݏ悵�Ă̕ω����w���֐��I�ɂ���
        affect = pow(affect, pointLights[ligNo].pow);
            
        //���C�g�ɉe��������Z�����l���ŏI�I�ȃ��C�g�ɉ��Z����
        finalLig += lig * affect;
        
        
    }

    //�S�Ẵ|�C���g���C�g�̌������Z�������C�g��Ԃ�
    return finalLig;
}

float3 CalcLigFromSpotLight(float3 normal, float3 worldPos, float specPower, uint tileIndex)
{
    //�S�ẴX�|�b�g���C�g�̌��ʂ𑫂����ŏI�I�ȃ��C�g
    float3 finalLig = { 0.0f, 0.0f, 0.0f };
    
    //�܂܂��^�C���̉e���̊J�n�ʒu�ƏI���ʒu���v�Z����
    uint lightStart = tileIndex * numSpotLight;
    uint lightEnd = lightStart + numSpotLight;
    
    for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++)
    {
        uint ligNo = spotLightListInTile[lightListIndex];
        if (ligNo == 0xffffffff)
        {
            // ���̃^�C���Ɋ܂܂��|�C���g���C�g�͂����Ȃ�
            break;
        }
        
        //�T�[�t�F�C�X�ɓ��˂���X�|�b�g���C�g�̌��̌��������߂�
        float3 ligDir = normalize(worldPos - spotLights[ligNo].position);
        //��������T�[�t�F�C�X�܂ł̋������v�Z
        float distance = length(worldPos - spotLights[ligNo].position);
        
        //���C�e�B���O�̌v�Z
        float3 lig = CalcLighting(ligDir, spotLights[ligNo].color, normal, worldPos, specPower);
     
        //�e�����̌v�Z
        //���������ɂ��e���������߂�
        float distanceAffect = pow(1.0f - min(1.0f, distance / spotLights[ligNo].range), spotLights[ligNo].rangePow);
        
        //���ˌ��Ǝˏo�����̊p�x�ɂ��e���������߂�
        //���ˌ��Ǝˏo�����̊p�x�����߂�
        float angleLigToPixel = dot(ligDir, spotLights[ligNo].direction);
        angleLigToPixel = abs(acos(angleLigToPixel));
        
        //�p�x�ɔ�Ⴕ�ď������Ȃ��Ă����e�������v�Z����
        float angleAffect = pow(max(0.0f, 1.0f - 1.0f / spotLights[ligNo].angle * angleLigToPixel), spotLights[ligNo].anglePow);
        
        //�e��������Z�������C�g���ŏI�I�ȃ��C�g�ɉ��Z����
        finalLig += lig * distanceAffect * angleAffect;
    }

    //�ŏI�I�ȃ��C�g��Ԃ�
    return finalLig;
}


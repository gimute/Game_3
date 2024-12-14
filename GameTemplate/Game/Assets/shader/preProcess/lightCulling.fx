///////////////////////////////////////////////////////
//�萔
///////////////////////////////////////////////////////////
static const int MAX_POINT_LIGHT = 250; // �|�C���g���C�g�̍ő吔
static const int MAX_SPOT_LIGHT = 250; // �X�|�b�g���C�g�̍ő吔

// ��x�Ɏ��s�����X���b�h��
#define TILE_WIDTH  16
#define TILE_HEIGHT 16

// �^�C���̑���
#define TILE_SIZE (TILE_WIDTH * TILE_HEIGHT)

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
    float3 position; //���W
    int isUse; //�g�p���t���O
    float3 color; //���C�g�̃J���[
    float renge; //�e���͈�
    float3 positionInView; //�J������Ԃł̍��W
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
    float3 positionInView;  //�J������Ԃł̍��W
    float rangePow; //�����ɂ��e�����̗ݏ搔
    float3 directionInView; // �J������Ԃł̎ˏo�����B
    float anglePow; //�p�x�ɂ��e�����̗ݏ搔
};

///////////////////////////////////////////////////////////
//�萔�o�b�t�@�[
///////////////////////////////////////////////////////////
cbuffer cbCameraParam : register(b0)
{
    float4x4 mtxProj;
    float4x4 mtxProjInv;
    float4x4 mtxViewRot;
    float4 screenParam;
}

cbuffer LightCb : register(b1)
{
    //���C�g���
    DirectionalLight directionalLight; //�f�B���N�V�������C�g
    PointLight pointLights[MAX_POINT_LIGHT]; //�|�C���g���C�g�̔z��
    SpotLight spotLights[MAX_SPOT_LIGHT]; //�X�|�b�g���C�g�̔z��
    float3 eyePos; //���_
    int numPointLight; //�|�C���g���C�g�̐�
    float3 ambientLig; //����
    int numSpotLight; //�X�|�b�g���C�g�̐�
    float3 eyeDir; //�����̕���
    
    //���̑�
    float4x4 mViewProjInv; //�Q�[���J�����̃r���[�v���W�F�N�V�����s��̋t�s��
    
    float4x4 mlvp; //�V���h�E�p���C�g�J�����̃r���[�v���W�F�N�V�����s��
    
    float3 ligCameraPos; //�V���h�E�}�b�v�p�̃��C�g�J�����̃|�W�V����
};

//�[�x�e�N�X�`��
Texture2D depthTexture : register(t0);

//�o�͗p�̃o�b�t�@�[
RWStructuredBuffer<uint> rwPointLightIndices : register(u0); //�|�C���g���C�g�C���f�b�N�X�o�b�t�@�[
RWStructuredBuffer<uint> rwSpotLightIndices : register(u1); // �X�|�b�g���C�g�C���f�b�N�X�o�b�t�@�[


// ���L������
// groupshared�����Ȃ̂��킩��Ȃ����ǒP���ɋ��L�ł��邾���ŕ��ʂ̕ϐ��Ȃ񂩂�
groupshared uint sMinZ; // �^�C���̍ŏ��[�x
groupshared uint sMaxZ; // �^�C���̍ő�[�x
groupshared uint sTilePointLightIndices[MAX_POINT_LIGHT]; // �^�C���ɐڐG���Ă���|�C���g���C�g�̃C���f�b�N�X
groupshared uint sTileNumPointLights; // �^�C���ɐڐG���Ă���|�C���g���C�g�̐�
groupshared uint sTileSpotLightIndices[MAX_SPOT_LIGHT]; //�@�^�C���ɐڐG���Ă���X�|�b�g���C�g�̃C���f�b�N�X
groupshared uint sTileNumSpotLights; //�@�^�C���ɐڐG���Ă���X�|�b�g���C�g�̐��B
groupshared uint ligNum = 0;

/*!
 * @brief �^�C�����Ƃ̎����䕽�ʂ����߂�
 */
void GetTileFrustumPlane(out float4 frustumPlanes[6], uint3 groupId)
{
    // �^�C���̍ő�E�ŏ��[�x�𕂓������_�ɕϊ�
    float minTileZ = asfloat(sMinZ);
    float maxTileZ = asfloat(sMaxZ);

    
    float2 tileScale = screenParam.zw * rcp(float(2 * TILE_WIDTH));
    float2 tileBias = tileScale - float2(groupId.xy);

    float4 c1 = float4(mtxProj._11 * tileScale.x, 0.0, tileBias.x, 0.0);
    float4 c2 = float4(0.0, -mtxProj._22 * tileScale.y, tileBias.y, 0.0);
    float4 c4 = float4(0.0, 0.0, 1.0, 0.0);

    frustumPlanes[0] = c4 - c1; // Right
    frustumPlanes[1] = c4 + c1; // Left
    frustumPlanes[2] = c4 - c2; // Top
    frustumPlanes[3] = c4 + c2; // Bottom
    frustumPlanes[4] = float4(0.0, 0.0, 1.0, -minTileZ);    //��O
    frustumPlanes[5] = float4(0.0, 0.0, -1.0, maxTileZ);    //��

    // �@�������K������Ă��Ȃ�4�ʂɂ��Ă������K������
    [unroll]
    for (uint i = 0; i < 4; ++i)
    {
        frustumPlanes[i] *= rcp(length(frustumPlanes[i].xyz));
    }
}

/*!
 * @brief �J������Ԃł̍��W���v�Z����
 */
float3 ComputePositionInCamera(uint2 globalCoords)
{
    float2 st = ((float2) globalCoords + 0.5) * rcp(screenParam.zw);
    st = st * float2(2.0, -2.0) - float2(1.0, -1.0);
    float3 screenPos;
    screenPos.xy = st.xy;
    screenPos.z = depthTexture.Load(uint3(globalCoords, 0.0f));
    float4 cameraPos = mul(mtxProjInv, float4(screenPos, 1.0f));

    return cameraPos.xyz / cameraPos.w;
}

/*!
 * @brief ���ݒ������̃^�C���Ɋ܂܂�Ă���X�|�b�g���C�g�̃C���f�b�N�X�̔z����쐬
 */
void CreateSpotLightIndexArrayInTile(uint threadNoInTile, float4 frustumPlanes[6])
{
    for (uint lightIndex = threadNoInTile; lightIndex < MAX_SPOT_LIGHT; lightIndex += TILE_SIZE)
    {
        SpotLight light = spotLights[lightIndex];
        if (light.isUse)
        {
            // �^�C���Ƃ̔���
            bool inFrustum = true;
            for (uint i = 0; i < 6; ++i)
            {
                // ���C�g�̍��W�ƕ��ʂ̖@���Ƃœ��ς��g���āA
                // ���C�g�ƕ��ʂƂ̋����i��������j���v�Z����
                float4 lp = float4(light.positionInView, 1.0f);
                float d = dot(frustumPlanes[i], lp);

                // ���C�g�ƕ��ʂ̋������g���āA�Փ˔�����s��
                inFrustum = inFrustum && (d >= -light.range);
            }

            // �^�C���ƏՓ˂��Ă���ꍇ
            if (inFrustum)
            {
                // �Փ˂����|�C���g���C�g�̔ԍ����e�����X�g�ɐς�ł���
                uint listIndex;
                InterlockedAdd(sTileNumSpotLights, 1, listIndex);
                sTileSpotLightIndices[listIndex] = lightIndex;
            }
        }
    }
}

/*!
 * @brief ���ݒ������̃^�C���Ɋ܂܂�Ă���|�C���g���C�g�̃C���f�b�N�X�̔z����쐬�B
 */
void CreatePointLightIndexArrayInTile(uint threadNoInTile, float4 frustumPlanes[6])
{
    for (uint lightIndex = threadNoInTile; lightIndex < MAX_POINT_LIGHT; lightIndex += TILE_SIZE)
    {
        PointLight light = pointLights[lightIndex];
        if (light.isUse)
        {
            // �^�C���Ƃ̔���
            bool inFrustum = true;
            for (uint i = 0; i < 6; ++i)
            {
                // ���C�g�̍��W�ƕ��ʂ̖@���Ƃœ��ς��g���āA
                // ���C�g�ƕ��ʂƂ̋����i��������j���v�Z����
                float4 lp = float4(light.positionInView, 1.0f);
                float d = dot(frustumPlanes[i], lp);

                // ���C�g�ƕ��ʂ̋������g���āA�Փ˔�����s��
                inFrustum = inFrustum && (d >= -light.renge);
            }

            // �^�C���ƏՓ˂��Ă���ꍇ
            if (inFrustum)
            {
                // �Փ˂����|�C���g���C�g�̔ԍ����e�����X�g�ɐς�ł���
                uint listIndex;
                InterlockedAdd(sTileNumPointLights, 1, listIndex);
                sTilePointLightIndices[listIndex] = lightIndex;
            }
        }
    }
}

/*!
 * @brief �^�C���Ɋ܂܂�Ă��郉�C�g�̔ԍ����o�͗p�̃��X�g�ɏ������݁B
 */
void WriteLightIindexInTileToList(uint threadNoInTile, uint2 frameUV)
{
    uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
    uint tileIndex = floor(frameUV.x / TILE_WIDTH) + floor(frameUV.y / TILE_WIDTH) * numCellX;

    // �|�C���g���C�g�̔ԍ����o��  
    uint lightStart = numPointLight * tileIndex;
    for (uint lightIndex = threadNoInTile; lightIndex < sTileNumPointLights; lightIndex += TILE_SIZE)
    {
        rwPointLightIndices[lightStart + lightIndex] = sTilePointLightIndices[lightIndex];
    }
    // �Ō�ɔԕ���ݒ肷��
    if ((threadNoInTile == 0) && (sTileNumPointLights < numPointLight))
    {
        // -1�Ŕԕ�
        rwPointLightIndices[lightStart + sTileNumPointLights] = 0xffffffff;
    }
    
    // �����ăX�|�b�g���C�g�̔ԍ����o�́B
    lightStart = numSpotLight * tileIndex;
    for (uint lightIndex = threadNoInTile; lightIndex < sTileNumSpotLights; lightIndex += TILE_SIZE)
    {
        rwSpotLightIndices[lightStart + lightIndex] = sTileSpotLightIndices[lightIndex];
    }
    // �Ō�ɔԕ���ݒ肷��
    if ((threadNoInTile == 0) && (sTileNumSpotLights < numSpotLight))
    {
        // -1�Ŕԕ�
        rwSpotLightIndices[lightStart + sTileNumSpotLights] = 0xffffffff;
    }
}

/*!
 * @brief CSMain
 */
[numthreads(TILE_WIDTH, TILE_HEIGHT, 1)]
void CSMain(
    uint3 groupId : SV_GroupID,
    uint3 dispatchThreadId : SV_DispatchThreadID,
    uint3 groupThreadId : SV_GroupThreadID)
{
    // step-7 �^�C�����ł̃C���f�b�N�X�����߂�
    // groupThreadId�̓O���[�v���ł̃X���b�h�ԍ�
    // ������g���āA�O���[�v���ł̃X���b�h�ԍ����v�Z����
    uint groupIndex = groupThreadId.y * TILE_WIDTH + groupThreadId.x;

    // ���L������������������
    if (groupIndex == 0)
    {
        sTileNumPointLights = 0;
        sTileNumSpotLights = 0;
        sMinZ = 0x7F7FFFFF; // float�̍ő�l
        sMaxZ = 0;
    }

    // ���̃X���b�h���S������s�N�Z���̃J������Ԃł̍��W���v�Z����
    uint2 frameUV = dispatchThreadId.xy;

    // �r���[��Ԃł̍��W���v�Z����
    float3 posInView = ComputePositionInCamera(frameUV);

    // ���ׂẴX���b�h�������ɓ��B����܂œ��������
    GroupMemoryBarrierWithGroupSync();

    if (groupThreadId.x <= screenParam.z && groupThreadId.y <= screenParam.w)
    {
        // �^�C���̍ő�E�ŏ��[�x�����߂�
        // ���̏����͕��񂷂�X���b�h���ׂĂŔr���I�ɏ��������
        InterlockedMin(sMinZ, asuint(posInView.z));
        InterlockedMax(sMaxZ, asuint(posInView.z));
    }
    
    // �����œ�������邱�ƂŃ^�C���̍ő�E�ŏ��[�x�𐳂������̂ɂ���
    GroupMemoryBarrierWithGroupSync();

    if (groupThreadId.x <= screenParam.z && groupThreadId.y <= screenParam.w)
    {
        // �^�C���̎�������\������6�̕��ʂ����߂�
        float4 frustumPlanes[6];

        // ���̊֐��̒��ŁA������\������6���ʂ��v�Z���Ă���
        GetTileFrustumPlane(frustumPlanes, groupId);

        // �^�C���Ɋ܂܂�Ă���|�C���g���C�g�̃C���f�b�N�X�̔z����쐬����B
        CreatePointLightIndexArrayInTile(groupIndex, frustumPlanes);
        // �^�C���Ɋ܂܂�Ă���X�|�b�g���C�g�̃C���f�b�N�X�̔z����쐬����B
        CreateSpotLightIndexArrayInTile(groupIndex, frustumPlanes);
    }
    // �����œ��������ƁAsTileSpotLightIndices��sTilePointLightIndices��
    // �^�C���ƏՓ˂��Ă��郉�C�g�̃C���f�b�N�X���ς܂�Ă���
    GroupMemoryBarrierWithGroupSync();

    if (groupThreadId.x <= screenParam.z && groupThreadId.y <= screenParam.w)
    {
        // ���C�g�C���f�b�N�X���o�̓o�b�t�@�[�ɏo��
        WriteLightIindexInTileToList(groupIndex, frameUV);
    }
}

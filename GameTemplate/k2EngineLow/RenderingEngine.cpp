#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
    RenderingEngine::RenderingEngine()
    {

    }
    RenderingEngine::~RenderingEngine()
    {

    }

    void RenderingEngine::Init()
    {
        InitMainRenderTarget();

        InitGBuffer();
        
        m_shadowMapRender.Init();
        
        //�f�B�t�@�[�h���C�e�B���O�̏�����
        InitDeferredLighting();

        //�|�X�g�G�t�F�N�g������
        m_postEffect.Init(
            m_mainRenderTarget
            );

        //�ŏI�I�ȊG���t���[���o�b�t�@�[�ɃR�s�[���邽�߂̃X�v���C�g������
        InitCopyMainRenderTargetToFrameBufferSprite();

        //���C�g�J�����O��������
        //�[�x�l���g���̂�depth�����_�����O�^�[�Q�b�g�̃e�N�X�`��
        //���C�g�̏�񂪂���̂Ńf�B�t�@�[�h���C�e�B���O�̒萔�o�b�t�@
        //�|�C���g���C�g�����C�g�J�����O�������ʂ��󂯎�邽�߂̃X�g���N�`���[�h�o�b�t�@�[
        //���̎O�𑗂�
        m_lightCulling.Init(
            m_depthRT.GetRenderTargetTexture(),
            m_diferredLightingSprite.GetExpandConstantBufferGPU(),
            m_pointLightNoListInTileUAV,
            m_spotLightNoListInTileUAV
        );

        m_volumeLightRender.Init();

        //G-Buffer���ؗp/////////////////////////////////////////////////////////
        SpriteInitData spData;
        spData.m_width = g_graphicsEngine->GetFrameBufferWidth();;
        spData.m_height = g_graphicsEngine->GetFrameBufferHeight();
        spData.m_fxFilePath = "Assets/shader/sprite.fx";
        //spData.m_textures[0] = &albedRT.GetRenderTargetTexture();
        //spData.m_textures[0] = &normalSpecRT.GetRenderTargetTexture();
        spData.m_textures[0] = &m_depthRT.GetRenderTargetTexture();
        m_GBufferTest.Init(spData);
        /////////////////////////////////////////////////////////////////////////

        
    }

    void RenderingEngine::InitMainRenderTarget()
    {
        //���C�������_�����O�^�[�Q�b�g��������
        m_mainRenderTarget.Create(
            g_graphicsEngine->GetFrameBufferWidth(),
            g_graphicsEngine->GetFrameBufferHeight(),
            1, 
            1,
            g_mainRenderTargetFormat.colorBufferFormat,
            g_mainRenderTargetFormat.depthBufferFormat
        );
    }

    void RenderingEngine::InitGBuffer()
    {
        //G-Buffer������
        //�A���x�h�J���[�������ݗp�̃����_�[�^�[�Q�b�g�쐬
        m_albedRT.Create(
            g_graphicsEngine->GetFrameBufferWidth(), 
            g_graphicsEngine->GetFrameBufferHeight(),
            1, 
            1,
            g_albedColorBuffer,
            DXGI_FORMAT_D32_FLOAT
        );
        //�@���������ݗp�̃����_�����O�^�[�Q�b�g�쐬
        m_normalSpecRT.Create(
            g_graphicsEngine->GetFrameBufferWidth(), 
            g_graphicsEngine->GetFrameBufferHeight(),
            1, 
            1,
            g_normalSpecBuffer,
            DXGI_FORMAT_UNKNOWN
        );
        //�[�x�l�������ݗp�̃����_�����O�^�[�Q�b�g�쐬
        m_depthRT.Create(
            g_graphicsEngine->GetFrameBufferWidth(), 
            g_graphicsEngine->GetFrameBufferHeight(),
            1, 
            1,
            g_depthBuffer,
            DXGI_FORMAT_D32_FLOAT
        );
    }

    void RenderingEngine::InitDeferredLighting()
    {
        //�^�C�����Ƃ̃|�C���g���C�g�̔ԍ����L�^���郊�X�g��UAV���쐬
        //�����Ƀf�[�^������̂̓��C�g�J�����O�N���X�����A�g���̂̓f�B�t�@�[�h���C�e�B���O�̎��Ȃ̂ŁA
        //�����_�����O�G���W���ŗp�ӂ��āA��������C�g�J�����O�ɋ��L����`�Ŏg��(�t�ł��ǂ��̂ł́H)
        m_pointLightNoListInTileUAV.Init(
            sizeof(int),
            MAX_POINT_LIGHT * NUM_TILE,
            nullptr
        );

        //�^�C�����Ƃ̃X�|�b�g���C�g�̔ԍ����L�^���郊�X�g��UAV���쐬
        m_spotLightNoListInTileUAV.Init(
            sizeof(int),
            MAX_SPOT_LIGHT * NUM_TILE,
            nullptr
        );

        //�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g�̏�����
        InitDiferrdLightingSprite();
    }

    void RenderingEngine::InitDiferrdLightingSprite()
    {
        //�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g��������
        SpriteInitData spriteInitData;
        //���ƍ����̓t���[���o�b�t�@�[�Ɠ���
        spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();;
        spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
        //�g�p����e�N�X�`��
        spriteInitData.m_textures[0] = &m_albedRT.GetRenderTargetTexture();
        spriteInitData.m_textures[1] = &m_normalSpecRT.GetRenderTargetTexture();
        spriteInitData.m_textures[2] = &m_depthRT.GetRenderTargetTexture();
        spriteInitData.m_textures[3] = &(m_shadowMapRender.GetShadowMap());

        //�g�p����V�F�[�_�[�ƒ萔�o�b�t�@�[
        spriteInitData.m_fxFilePath = "Assets/shader/deferredLighting.fx";
        //spriteInitData.m_psEntryPoinFunc = ""
        spriteInitData.m_expandConstantBuffer = &m_deferredLightingCB;
        spriteInitData.m_expandConstantBufferSize = sizeof(m_deferredLightingCB);
        spriteInitData.m_expandShaderResoruceView[0] = &m_pointLightNoListInTileUAV;
        spriteInitData.m_expandShaderResoruceView[1] = &m_spotLightNoListInTileUAV;

        //�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g
        spriteInitData.m_colorBufferFormat[0] = g_mainRenderTargetFormat.colorBufferFormat;
        //�X�v���C�g��������
        m_diferredLightingSprite.Init(spriteInitData);
    }

    void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
    {
        SpriteInitData spriteInitData;

        //�e�N�X�`����m_mainRenderTarget�̃J���[�o�b�t�@�[
        spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

        //���ƍ����̓t���[���o�b�t�@�Ɠ���
        spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
        spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();

        spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

        //�V�F�[�_�[���w��
        spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

        //�����������g���āA�X�v���C�g��������
        m_copyMainRtToFrameBufferSprite.Init(spriteInitData);
    }


    void RenderingEngine::Execute(RenderContext& rc)
    {
        //���C�������_�����O�^�[�Q�b�g�̃N���A�͂��Ȃ��Ă����ǑS���㏑�������̂ŃX���[
     
        //���C�g�̃f�[�^���R�s�[
        m_deferredLightingCB.m_light = g_sceneLight->GetSceneLight();

        //�V���h�E�}�b�v�쐬
        m_shadowMapRender.Render(rc, g_sceneLight->GetSceneLight().directionalLight.direction, m_renderObjects);



        //G-Buffer�ւ̕`��
        RenderToGBuffer(rc);

        //���C�g�J�����O
        m_lightCulling.Execute(rc);

        //�f�B�t�@�[�h���C�e�B���O
        DeferredLighting(rc);
        
        //�t�H���[�h�����_�����O
        ForwardRendering(rc);

        //�|�X�g�G�t�F�N�g
        m_postEffect.Render(rc, m_mainRenderTarget);

        //�����_�����O����t���[���o�b�t�@�[�ɖ߂�
        g_graphicsEngine->ChangeRenderTargetToFrameBuffer(rc);

        

        //�ŏI�I�ȉ�ʂ�`��
        m_copyMainRtToFrameBufferSprite.Draw(rc);

        

        //G-Buffer���ؗp
        //m_GBufferTest.Draw(rc);

        ///////////////////////////////////////////////////
        {
            /*SpriteInitData InitDate;

            InitDate.m_fxFilePath = "Assets/shader/sprite.fx";

            InitDate.m_width = 1024;
            InitDate.m_height = 1024;

            InitDate.m_textures[0] = &m_shadowMapRender.GetShadowMap();

            Sprite testSp;

            testSp.Init(InitDate);

            testSp.Update({ 600.0f,300.0f,0.0f }, Quaternion::Identity, { 0.3f,0.3f,0.3f });

            testSp.Draw(rc);*/
        }
        ///////////////////////////////////////////////////
        
        

        // �o�^����Ă���`��I�u�W�F�N�g���N���A
        m_renderObjects.clear();
    }

    void RenderingEngine::RenderToGBuffer(RenderContext& rc)
    {
        //G-Buffer�������_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
        rc.WaitUntilToPossibleSetRenderTargets(sizeof(rts) / sizeof(rts[0]), rts);

        //�����_�����O�^�[�Q�b�g��ݒ�
        rc.SetRenderTargetsAndViewport(sizeof(rts) / sizeof(rts[0]), rts);

        //�����_�����O�^�[�Q�b�g���N���A
        rc.ClearRenderTargetViews(sizeof(rts) / sizeof(rts[0]), rts);

        for (auto& renderObj : m_renderObjects) {
            renderObj->OnRenderToGBuffer(rc);
        }

        //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
        rc.WaitUntilFinishDrawingToRenderTargets(sizeof(rts) / sizeof(rts[0]), rts);   
    }

    void RenderingEngine::DeferredLighting(RenderContext& rc)
    {
        //���C�g�r���[�v���W�F�N�V�����s����󂯎��
        m_deferredLightingCB.m_lvp = m_shadowMapRender.GetLVPMatrix();
        //�V���h�E�}�b�v�p�̃��C�g�J�����̈ʒu���󂯎��
        m_deferredLightingCB.m_shadowLightPos = m_shadowMapRender.GetLigCameraPos();
        //�Q�[���J�����̃r���[�v���W�F�N�V�����s��̋t�s����󂯎��
        m_deferredLightingCB.m_viewProjIn = g_camera3D->GetViewProjectionMatrixInv();

        //�����_�����O������C�������_�����O�^�[�Q�b�g�ɕύX
        rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
        rc.SetRenderTargetAndViewport(m_mainRenderTarget);

        // G-Buffer�̓��e�����ɂ��ăf�B�t�@�[�h���C�e�B���O
        m_diferredLightingSprite.Draw(rc);

        //���C�������_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
        rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
    }

    void RenderingEngine::ForwardRendering(RenderContext& rc)
    {
        //�g�������_�����O�^�[�Q�b�g�̏���
        rc.WaitUntilToPossibleSetRenderTarget(m_depthRT);
        rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);

        //�{�����[�����C�g�`��
        m_volumeLightRender.Render(
            rc,
            m_mainRenderTarget.GetRTVCpuDescriptorHandle(),
            m_depthRT.GetDSVCpuDescriptorHandle()
        );
        //�g���������_�����O�^�[�Q�b�g�̂̏������ݏI���҂�
        rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
        rc.WaitUntilFinishDrawingToRenderTarget(m_depthRT);
    }

}

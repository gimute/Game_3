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
        
        //ディファードライティングの初期化
        InitDeferredLighting();

        //ポストエフェクト初期化
        m_postEffect.Init(
            m_mainRenderTarget
            );

        //最終的な絵をフレームバッファーにコピーするためのスプライト初期化
        InitCopyMainRenderTargetToFrameBufferSprite();

        //ライトカリングを初期化
        //深度値を使うのでdepthレンダリングターゲットのテクスチャ
        //ライトの情報がいるのでディファードライティングの定数バッファ
        //ポイントライトをライトカリングした結果を受け取るためのストラクチャードバッファー
        //この三つを送る
        m_lightCulling.Init(
            m_depthRT.GetRenderTargetTexture(),
            m_diferredLightingSprite.GetExpandConstantBufferGPU(),
            m_pointLightNoListInTileUAV,
            m_spotLightNoListInTileUAV
        );

        m_volumeLightRender.Init();

        //G-Buffer検証用/////////////////////////////////////////////////////////
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
        //メインレンダリングターゲットを初期化
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
        //G-Bufferを準備
        //アルベドカラー書き込み用のレンダーターゲット作成
        m_albedRT.Create(
            g_graphicsEngine->GetFrameBufferWidth(), 
            g_graphicsEngine->GetFrameBufferHeight(),
            1, 
            1,
            g_albedColorBuffer,
            DXGI_FORMAT_D32_FLOAT
        );
        //法線書き込み用のレンダリングターゲット作成
        m_normalSpecRT.Create(
            g_graphicsEngine->GetFrameBufferWidth(), 
            g_graphicsEngine->GetFrameBufferHeight(),
            1, 
            1,
            g_normalSpecBuffer,
            DXGI_FORMAT_UNKNOWN
        );
        //深度値書き込み用のレンダリングターゲット作成
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
        //タイルごとのポイントライトの番号を記録するリストのUAVを作成
        //こいつにデータを入れるのはライトカリングクラスだが、使うのはディファードライティングの時なので、
        //レンダリングエンジンで用意して、それをライトカリングに共有する形で使う(逆でも良いのでは？)
        m_pointLightNoListInTileUAV.Init(
            sizeof(int),
            MAX_POINT_LIGHT * NUM_TILE,
            nullptr
        );

        //タイルごとのスポットライトの番号を記録するリストのUAVを作成
        m_spotLightNoListInTileUAV.Init(
            sizeof(int),
            MAX_SPOT_LIGHT * NUM_TILE,
            nullptr
        );

        //ディファードライティング用のスプライトの初期化
        InitDiferrdLightingSprite();
    }

    void RenderingEngine::InitDiferrdLightingSprite()
    {
        //ディファードライティング用のスプライトを初期化
        SpriteInitData spriteInitData;
        //幅と高さはフレームバッファーと同じ
        spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();;
        spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
        //使用するテクスチャ
        spriteInitData.m_textures[0] = &m_albedRT.GetRenderTargetTexture();
        spriteInitData.m_textures[1] = &m_normalSpecRT.GetRenderTargetTexture();
        spriteInitData.m_textures[2] = &m_depthRT.GetRenderTargetTexture();
        spriteInitData.m_textures[3] = &(m_shadowMapRender.GetShadowMap());

        //使用するシェーダーと定数バッファー
        spriteInitData.m_fxFilePath = "Assets/shader/deferredLighting.fx";
        //spriteInitData.m_psEntryPoinFunc = ""
        spriteInitData.m_expandConstantBuffer = &m_deferredLightingCB;
        spriteInitData.m_expandConstantBufferSize = sizeof(m_deferredLightingCB);
        spriteInitData.m_expandShaderResoruceView[0] = &m_pointLightNoListInTileUAV;
        spriteInitData.m_expandShaderResoruceView[1] = &m_spotLightNoListInTileUAV;

        //レンダリングターゲットのフォーマット
        spriteInitData.m_colorBufferFormat[0] = g_mainRenderTargetFormat.colorBufferFormat;
        //スプライトを初期化
        m_diferredLightingSprite.Init(spriteInitData);
    }

    void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
    {
        SpriteInitData spriteInitData;

        //テクスチャはm_mainRenderTargetのカラーバッファー
        spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

        //幅と高さはフレームバッファと同じ
        spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
        spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();

        spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

        //シェーダーを指定
        spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

        //初期化情報を使って、スプライトを初期化
        m_copyMainRtToFrameBufferSprite.Init(spriteInitData);
    }


    void RenderingEngine::Execute(RenderContext& rc)
    {
        //メインレンダリングターゲットのクリアはしなくても結局全部上書きされるのでスルー
     
        //ライトのデータをコピー
        m_deferredLightingCB.m_light = g_sceneLight->GetSceneLight();

        //シャドウマップ作成
        m_shadowMapRender.Render(rc, g_sceneLight->GetSceneLight().directionalLight.direction, m_renderObjects);



        //G-Bufferへの描画
        RenderToGBuffer(rc);

        //ライトカリング
        m_lightCulling.Execute(rc);

        //ディファードライティング
        DeferredLighting(rc);
        
        //フォワードレンダリング
        ForwardRendering(rc);

        //ポストエフェクト
        m_postEffect.Render(rc, m_mainRenderTarget);

        //レンダリング先をフレームバッファーに戻す
        g_graphicsEngine->ChangeRenderTargetToFrameBuffer(rc);

        

        //最終的な画面を描画
        m_copyMainRtToFrameBufferSprite.Draw(rc);

        

        //G-Buffer検証用
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
        
        

        // 登録されている描画オブジェクトをクリア
        m_renderObjects.clear();
    }

    void RenderingEngine::RenderToGBuffer(RenderContext& rc)
    {
        //G-Bufferがレンダリングターゲットとして設定できるようになるまで待つ
        rc.WaitUntilToPossibleSetRenderTargets(sizeof(rts) / sizeof(rts[0]), rts);

        //レンダリングターゲットを設定
        rc.SetRenderTargetsAndViewport(sizeof(rts) / sizeof(rts[0]), rts);

        //レンダリングターゲットをクリア
        rc.ClearRenderTargetViews(sizeof(rts) / sizeof(rts[0]), rts);

        for (auto& renderObj : m_renderObjects) {
            renderObj->OnRenderToGBuffer(rc);
        }

        //レンダリングターゲットへの書き込み終了待ち
        rc.WaitUntilFinishDrawingToRenderTargets(sizeof(rts) / sizeof(rts[0]), rts);   
    }

    void RenderingEngine::DeferredLighting(RenderContext& rc)
    {
        //ライトビュープロジェクション行列を受け取る
        m_deferredLightingCB.m_lvp = m_shadowMapRender.GetLVPMatrix();
        //シャドウマップ用のライトカメラの位置を受け取る
        m_deferredLightingCB.m_shadowLightPos = m_shadowMapRender.GetLigCameraPos();
        //ゲームカメラのビュープロジェクション行列の逆行列を受け取る
        m_deferredLightingCB.m_viewProjIn = g_camera3D->GetViewProjectionMatrixInv();

        //レンダリング先をメインレンダリングターゲットに変更
        rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
        rc.SetRenderTargetAndViewport(m_mainRenderTarget);

        // G-Bufferの内容を元にしてディファードライティング
        m_diferredLightingSprite.Draw(rc);

        //メインレンダリングターゲットへの書き込み終了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
    }

    void RenderingEngine::ForwardRendering(RenderContext& rc)
    {
        //使うレンダリングターゲットの準備
        rc.WaitUntilToPossibleSetRenderTarget(m_depthRT);
        rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);

        //ボリュームライト描画
        m_volumeLightRender.Render(
            rc,
            m_mainRenderTarget.GetRTVCpuDescriptorHandle(),
            m_depthRT.GetDSVCpuDescriptorHandle()
        );
        //使ったレンダリングターゲットのの書き込み終了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
        rc.WaitUntilFinishDrawingToRenderTarget(m_depthRT);
    }

}

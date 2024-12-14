#include "k2EngineLowPreCompile.h"
#include "VolumeLightBase.h"

//ボリュームライト

namespace nsK2EngineLow {
	VolumeLightBase::~VolumeLightBase()
	{
		//シーンから削除
		if (g_renderingEngine)
		{
			g_renderingEngine->RemoveVolumeLight(*this);
		}
	}

	void VolumeLightBase::Init(
		const void* lightData,
		const char* tkmFilePath,
		const char* psFinalEntryFunc
	){
		//ライトデータをセット
		SetLightData(lightData);

		//シーンライトに登録
		g_renderingEngine->AddVolumeSpotLight(*this);
		//ボリュームライトマップ描画のモデル初期化設定を行う
		//前面描画
		ModelInitData forntModelInitData;
		forntModelInitData.m_tkmFilePath = tkmFilePath;
		forntModelInitData.m_fxFilePath = "Assets/shader/DrawVolumeLightModel.fx";
		forntModelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->GetGBufferDepthTexture();
		forntModelInitData.m_colorBufferFormat[0] = g_drawVolumeLightMapFormat.colorBufferFormat;
		forntModelInitData.m_psEntryPointFunc = "PSMainFrontBackModel";
		forntModelInitData.m_cullMode = D3D12_CULL_MODE_BACK; //前面描画なので、背面カリング
		m_modelFront.Init(forntModelInitData);

		//背面描画
		ModelInitData backModelInitData;
		//カリングの設定以外前面描画と同じなので前面描画のデータを利用する
		backModelInitData = forntModelInitData;
		backModelInitData.m_cullMode = D3D12_CULL_MODE_FRONT;	//背面描画なので前面カリング
		m_modelBack.Init(backModelInitData);

		//最終描画
		SpriteInitData spriteInitData;
		spriteInitData.m_fxFilePath = "Assets/shader/DrawVolumeLightFinalSprite.fx";
		spriteInitData.m_vsEntryPointFunc = "VSFinal";
		spriteInitData.m_psEntryPoinFunc = psFinalEntryFunc;
		spriteInitData.m_colorBufferFormat[0] = g_mainRenderTargetFormat.colorBufferFormat;
		spriteInitData.m_textures[0] = &g_renderingEngine->GetGBufferAlbedoTexture();
		spriteInitData.m_textures[1] = &g_renderingEngine->GetVolumeLightRender().GetVolumeLightMapFrontTexture();
		spriteInitData.m_textures[2] = &g_renderingEngine->GetVolumeLightRender().GetVolumeLightMapBackTexture();
		spriteInitData.m_expandConstantBuffer = GetFinalCB();
		spriteInitData.m_expandConstantBufferSize = GetFinalCBSize();

		spriteInitData.m_width = FRAME_BUFFER_W;
		spriteInitData.m_height = FRAME_BUFFER_H;
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		m_final.Init(spriteInitData);
	}

	void VolumeLightBase::DrawToVolumeLightMapFront(RenderContext& rc)
	{
		m_modelFront.Draw(rc);
	}

	void VolumeLightBase::DrawToVolumeLightMapBack(RenderContext& rc)
	{
		m_modelBack.Draw(rc);
	}

	void VolumeLightBase::DrawFinal(RenderContext& rc)
	{
		PreDrawFinal(rc);
		m_final.Draw(rc);
	}
}

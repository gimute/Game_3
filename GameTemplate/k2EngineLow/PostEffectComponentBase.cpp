#include "k2EngineLowPreCompile.h"
#include "PostEffectComponentBase.h"

namespace nsK2EngineLow {
	void PostEffectComponentBase::Init(RenderTarget& mainRenderTarget)
	{
		OnInit(mainRenderTarget);

		// このメインレンダーターゲットへコピーするフラグoffで初期化したあと
		// メインレンダーターゲットへコピーするフラグonにしたらエラー吐かれるくね？
		if (IsCopyResultTextureToMainRenderTarget()) {
			SpriteInitData initData;
			initData.m_width = mainRenderTarget.GetWidth();
			initData.m_height = mainRenderTarget.GetHeight();
			initData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
			initData.m_fxFilePath = "Assets/shader/Sprite.fx";
			//これブルームだと輝度抽出テクスチャを使ってるから正しく機能しない
			initData.m_textures[0] = &GetResultTexture();
			m_copyMainRtSprite.Init(initData);
		}
	}

	void PostEffectComponentBase::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//ポストエフェクトが無効なら何もせずに返す
		if (!m_isEnable) {
			return;
		}


		
		//独自処理
		OnRender(rc, mainRenderTarget);

		//メインレンダリングターゲットにコピーする処理、そもそもメインレンダリングターゲットに描画してるから意味わからん
		if (IsCopyResultTextureToMainRenderTarget()) {
			// レンダリングターゲットとして利用できるまで待つ
			rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
			// レンダリングターゲットを設定
			rc.SetRenderTargetAndViewport(mainRenderTarget);
			// ポストエフェクトの結果をメインレンダリングターゲットに反映。
			m_copyMainRtSprite.Draw(rc);
			// レンダリングターゲットへの書き込み終了待ち
			rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
		}
	}

}

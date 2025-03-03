#include "k2EngineLowPreCompile.h"
#include "CenterBlur.h"

//センターブラー
namespace nsK2EngineLow {
	void CenterBlur::OnInit(RenderTarget& mainRenderTarget)
	{
		m_tsts.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			g_mainRenderTargetFormat.depthBufferFormat
		);

		//ブラーを適用するためのスプライトを初期化
		SpriteInitData spriteInitDate;
		//シェーダーファイルパスを指定
		spriteInitDate.m_fxFilePath = "Assets/shader/postEffect/centerBlur.fx";
		//幅と高さはmainRenderTargetと同じ
		spriteInitDate.m_width = mainRenderTarget.GetWidth();
		spriteInitDate.m_height = mainRenderTarget.GetHeight();
		//テクスチャはメインレンダリングターゲットのカラーバッファー
		spriteInitDate.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		//書き込むレンダリングターゲットのフォーマットを取得
		spriteInitDate.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
		//ブラーの強さを設定するための値を入れる定数バッファー
		spriteInitDate.m_expandConstantBuffer = &m_blurPower;
		spriteInitDate.m_expandConstantBufferSize = sizeof(m_blurPower);

		//用意したデータでスプライトを初期化
		m_centerBlur.Init(spriteInitDate);

		//ブラーを適用するためのスプライトを初期化
		SpriteInitData spriteInitDatea;
		//シェーダーファイルパスを指定
		spriteInitDatea.m_fxFilePath = "Assets/shader/sprite.fx";
		//幅と高さはmainRenderTargetと同じ
		spriteInitDatea.m_width = m_tsts.GetWidth();
		spriteInitDatea.m_height = m_tsts.GetHeight();
		//テクスチャはメインレンダリングターゲットのカラーバッファー
		spriteInitDatea.m_textures[0] = &m_tsts.GetRenderTargetTexture();
		//書き込むレンダリングターゲットのフォーマットを取得
		spriteInitDatea.m_colorBufferFormat[0] = m_tsts.GetColorBufferFormat();

		//用意したデータでスプライトを初期化
		m_keka.Init(spriteInitDatea);
	}

	void CenterBlur::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		switch (m_fadeState)
		{
		case nsK2EngineLow::enCenterBlureIn:
			m_blurPower += g_gameTime->GetTrueFrameDeltaTime() * 2.0f;
			if (m_blurPower >= 1.0f)
			{
				m_blurPower = 1.0f;
				m_fadeState = enCenterBlureIdle;
			}
			break;

		case nsK2EngineLow::enCenterBlureOut:
			m_blurPower -= g_gameTime->GetTrueFrameDeltaTime() * 2.0f;
			if (m_blurPower <= 0.0f)
			{
				m_blurPower = 0.0f;
				m_fadeState = enCenterBlureIdle;
				Disable();
			}
			break;

		case nsK2EngineLow::enCenterBlureIdle:
			break;
		default:
			break;
		}

		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_tsts);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_tsts);
		// ブラーを適用
		m_centerBlur.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_tsts);


		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		// ブラーを適用
		m_keka.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	}

}
#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow {
	void Bloom::OnInit(RenderTarget& mainRenderTarget)
	{
		m_luminanceRenderTarget.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			DXGI_FORMAT_UNKNOWN
		);

		//輝度抽出用のスプライトを初期化
		//初期化情報を作成する
		SpriteInitData luminanceSpriteInitData;
		//輝度抽出用のシェーダーファイルパスを指定する
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect/bloom.fx";
		//頂点シェーダーのエントリーポイントを指定する
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		//今のところ送りたい情報が無いのでユーザー拡張コンスタントバッファーはスルー
		//luminanceSpriteInitData.m_expandConstantBuffer = ;
		//luminanceSpriteInitData.m_expandConstantBufferSize = sizeof();
		
		//スプライトの幅と高さはluminnceRenderTargetと同じ
		luminanceSpriteInitData.m_width = mainRenderTarget.GetWidth();
		luminanceSpriteInitData.m_height = mainRenderTarget.GetHeight();

		//テクスチャはメインレンダリングターゲットのカラーバッファー
		luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		// 描き込むレンダリングターゲットのフォーマットを指定する
		luminanceSpriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

		//スプライトを初期化
		m_luminanceSprite.Init(luminanceSpriteInitData);


		//ガウシアンブラーを初期化
		//gaussianBlur[0]は輝度テクスチャにガウシアンブラーをかける
		//[1][2][3]はそれぞれひとつ前のガウシアンブラーのテクスチャにガウシアンブラーをかける
		m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		// 最終合成用のスプライトを初期化する
		SpriteInitData finalSpriteInitData;
		// ボケテクスチャを4枚指定する
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();
		// 解像度はmainRenderTargetの幅と高さ
		finalSpriteInitData.m_width = mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = mainRenderTarget.GetHeight();
		// ぼかした画像を、通常の2Dとしてメインレンダリングターゲットに描画するので、
		// 2D用のシェーダーを使用する
		finalSpriteInitData.m_fxFilePath = "Assets/shader/postEffect/bloom.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		// ただし、加算合成で描画するので、アルファブレンディングモードを加算にする
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		finalSpriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

		m_finalSprite.Init(finalSpriteInitData);

	}

	void Bloom::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//輝度抽出
		// 輝度抽出用のレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
		// レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_luminanceRenderTarget);
		// 輝度抽出を行う
		m_luminanceSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);

		// ガウシアンブラーを4回実行する
		m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

		// 4枚のボケ画像を合成してメインレンダリングターゲットに加算合成
		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		// 最終合成
		m_finalSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	}
}
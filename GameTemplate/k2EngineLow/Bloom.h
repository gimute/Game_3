#pragma once

#include "PostEffectComponentBase.h"

namespace nsK2EngineLow {
	/// <summary>
	/// ブルーム
	/// </summary>
	class Bloom : public PostEffectComponentBase
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="mainRenderTarget">メインレンダーターゲット</param>
		void OnInit(RenderTarget& mainRenderTarget) override;
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc">レンダーコンテキスト</param>
		/// <param name="mainRenderTarget">メインレンダーターゲット</param>
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) override;


		//結果を返しそうな感じで書いてるけど全然嘘じゃない？
		Texture& GetResultTexture() override
		{
			return m_luminanceRenderTarget.GetRenderTargetTexture();
		};

	private:
		RenderTarget m_luminanceRenderTarget;	//輝度抽出用のレンダリングターゲット
		Sprite m_luminanceSprite;				//輝度抽出用のスプライト
		GaussianBlur m_gaussianBlur[4];			//ガウシアンブラー
		Sprite m_finalSprite;					//最終合成用のスプライト
	};


}



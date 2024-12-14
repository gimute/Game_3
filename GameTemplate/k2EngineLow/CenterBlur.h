#pragma once

#include "PostEffectComponentBase.h"

//中央ブラー
namespace nsK2EngineLow {
	
	/// <summary>
	/// 中央から外に向かうブラー
	/// </summary>
	class CenterBlur : public PostEffectComponentBase
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="mainRenderTarget"></param>
		void OnInit(RenderTarget& mainRenderTarget) override;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="mainRenderTarget"></param>
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) override;

	private:
		Sprite m_centerBlur;

		RenderTarget m_tsts;
		Sprite m_keka;
	};

}




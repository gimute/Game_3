#pragma once

#include "Bloom.h"
#include "CenterBlur.h"

namespace nsK2EngineLow {
	/// <summary>
	/// ポストエフェクト
	/// </summary>
	class PostEffect : public Noncopyable
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="mainRenderTarget">レンダリングターゲット</param>
		void Init(RenderTarget& mainRenderTarget);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc">レンダーコンテキスト</param>
		/// <param name="mainRenderTarget">メインレンダーターゲット</param>
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);


		void DisableCenterBlur()
		{
			m_centeBlur.Disable();
		}

		void EnableCenterBlur()
		{
			m_centeBlur.Enable();
		}

	private:
		Bloom m_bloom;	    //ブルーム
		CenterBlur m_centeBlur;
	};
}



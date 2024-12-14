#pragma once

namespace nsK2EngineLow {
	class PostEffectComponentBase : public Noncopyable
	{
	public:
		void Init(RenderTarget& mainRenderTarget);

		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// ポストエフェクトを無効にする
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
		}
		/// <summary>
		/// ポストエフェクトを有効にする。
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}
		/// <summary>
		/// ポストエフェクトが有効か判定。
		/// </summary>
		/// <returns></returns>
		bool IsEnable() const
		{
			return m_isEnable;
		}

		//このクラスを継承した子クラスの独自処理を入れる純粋仮想関数
		// 子クラスの初期化処理
		virtual void OnInit(RenderTarget& mainRenderTarget) = 0;
		// 子クラスの描画処理
		virtual void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) = 0;

		virtual Texture& GetResultTexture()
		{
			static Texture nullTexture;
			return nullTexture;
		}

		/// <summary>
		/// ポストの結果をメインレンダリングターゲットにコピーするかどうか
		/// </summary>
		/// <returns></returns>
		virtual bool IsCopyResultTextureToMainRenderTarget() const
		{
			return false;
		}


	private:
		bool m_isEnable = true;		//ポストエフェクトを有効にするか
		Sprite m_copyMainRtSprite;	//メインレンダリングターゲットに描画するためのスプライト。
	};
}



#pragma once


namespace {
	static const int MAX_TEXT_SIZE = 256;
}

namespace nsK2EngineLow {
	//フォントレンダー
	class FontRender : public IRenderer
	{
	public:
		FontRender() {};
		~FontRender() {};

		//表示する文字を設定
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}
		//表示する文字を取得
		const wchar_t* GetText() const
		{
			return m_text;
		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(Vector2 pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// 座標を取得
		/// </summary>
		/// <returns></returns>
		const Vector2& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// 拡大率を設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		
		/// <summary>
		/// 拡大率を取得
		/// </summary>
		/// <returns></returns>
		const float& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rotation">回転量、数字が増えると反時計回り、数字が減ると時計回り</param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// 回転を取得
		/// </summary>
		/// <returns></returns>
		const float& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		void SetColor(float r, float g, float b, float a)
		{
			SetColor({ r,g,b,a });
		}

		/// <summary>
		/// 色を取得
		/// </summary>
		/// <returns></returns>
		const Vector4& GetColor() const
		{
			return m_color;
		}

		/// <summary>
		/// 影のパラメータを設定。
		/// </summary>
		/// <param name="isDrawShadow">影を描画する？</param>
		/// <param name="shadowOffset">影を描画するときのピクセルのオフセット量。</param>
		/// <param name="shadowColor">影の色。</param>
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}

		/// <summary>
		/// ピボットを設定
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(Vector2 pivot)
		{
			m_pivot = pivot;
		}
		
		/// <summary>
		/// ピボットを取得
		/// </summary>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}


		//描画処理。
		void Draw(RenderContext& rc);

		//2Dの描画処理
		void OnRender2D(RenderContext& rc) override;


	private:
		Vector2 m_position = Vector2::Zero;
		float m_rotation = 0.0f;
		float m_scale = 1.0f;
		Vector4 m_color = g_vec4White;
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;

		wchar_t m_text[MAX_TEXT_SIZE];
		Font m_font;
	};
}




#pragma once
namespace nsK2EngineLow {
	class SpriteRender : public IRenderer
	{
	public:
		SpriteRender() {};
		~SpriteRender() {};

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="filePath">画像のファイルパス</param>
		/// <param name="w">横幅</param>
		/// <param name="h">縦幅</param>
		/// <param name="alphaBlendMode">アルファブレンディングモード</param>
		void Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="initData">スプライトの初期化データ</param>
		void Init(SpriteInitData initData)
		{
			m_sprite.Init(initData);
		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector2& pos)
		{
			m_position = { pos.x,pos.y,0.0f };
		}
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 座標を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// スケールを設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// スケールを取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// 回転を取得
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// ピボットを設定
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// ピボットを取得
		/// </summary>
		/// <returns></returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// 乗算カラーを設定
		/// </summary>
		/// <param name="mulColor"></param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
		/// <summary>
		/// 乗算カラーを取得
		/// </summary>
		/// <returns></returns>
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update()
		{
			m_sprite.Update(
				m_position,
				m_rotation,
				m_scale,
				m_pivot);
		}

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc"></param>
		/// <remarks>
		/// レンダリングエンジンに登録する処理
		/// </remarks>
		void Draw(RenderContext& rc);

		//2D描画パスから呼ばれる処理
		void OnRender2D(RenderContext& rc) override
		{
			m_sprite.Draw(rc);
		}

	private:
		Sprite		m_sprite;							//スプライト
		Vector3		m_position = Vector3::Zero;			//座標
		Quaternion	m_rotation = Quaternion::Identity;	//回転
		Vector3		m_scale = Vector3::One;				//スケール
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット
	};

}




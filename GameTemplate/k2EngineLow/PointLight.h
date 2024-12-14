#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// ポイントライト
	/// </summary>
	class PointLight : public Noncopyable
	{
	public:
		~PointLight();

		//初期化
		void Init();

		/// <summary>
		/// ライトの座標を設定
		/// </summary>
		/// <param name="position">ライトの座標</param>
		void SetPosition(const Vector3& position)
		{
			m_pointLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_pointLight->SetPosition(x, y, z);
		}
		/// <summary>
		/// 座標を取得
		/// </summary>
		/// <returns>ライトの座標</returns>
		const Vector3& GetPosition() const
		{
			return m_pointLight->GetPosition();
		}

		/// <summary>
		/// ライトのカラーを設定
		/// </summary>
		/// <param name="color">ライトのカラー</param>
		void SetColor(const Vector3& color)
		{
			m_pointLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_pointLight->SetColor(r, g, b);
		}
		/// <summary>
		/// ライトのカラーを取得
		/// </summary>
		/// <returns>ライトのカラー</returns>
		const Vector3& GetColor() const
		{
			return m_pointLight->GetColor();
		}

		/// <summary>
		/// 影響範囲を設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(float range)
		{
			m_pointLight->SetRange(range);
		}
		/// <summary>
		/// 影響範囲を取得
		/// </summary>
		/// <returns></returns>
		float GetRange() const
		{
			return m_pointLight->GetRange();
		}

		/// <summary>
		/// 影響率の累乗数を設定
		/// </summary>
		/// <param name="powParam"></param>
		void SetAffectPowParam(float powParam)
		{
			m_pointLight->SetAffectPowParam(powParam);
		}

		/// <summary>
		/// 生データを取得
		/// </summary>
		/// <returns></returns>
		const SPointLight& GetRawData() const
		{
			return *m_pointLight;
		}

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update()
		{
			m_pointLight->Updata();
		}
		
		
		

	private:
		SPointLight* m_pointLight = nullptr;	//使用するライトのポインタ
	};
}


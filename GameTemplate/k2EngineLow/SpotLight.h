#pragma once

namespace nsK2EngineLow {
	class SpotLight : public Noncopyable
	{
	public:
		~SpotLight();

		//初期化
		void Init();

		/// <summary>
		/// ライトの座標を設定
		/// </summary>
		/// <param name="position">ライトの座標</param>
		void SetPosition(const Vector3& position)
		{
			m_spotLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_spotLight->SetPosition(x, y, z);
		}
		/// <summary>
		/// ライトの座標を取得
		/// </summary>
		/// <returns>ライトの座標</returns>
		const Vector3& GetPosition() const
		{
			return m_spotLight->GetPosition();
		}

		/// <summary>
		/// ライトのカラーを設定
		/// </summary>
		/// <param name="color">ライトのカラー</param>
		void SetColor(const Vector3& color)
		{
			m_spotLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_spotLight->SetColor(r, g, b);
		}
		/// <summary>
		/// ライトのカラーの取得
		/// </summary>
		/// <returns>ライトのカラー</returns>
		const Vector3& GetColor() const
		{
			return m_spotLight->GetColor();
		}

		/// <summary>
		/// 射出方向を設定
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(const Vector3& direction)
		{
			m_spotLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_spotLight->SetDirection(x, y, z);
		}
		/// <summary>
		/// 射出方向を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirection() const
		{
			return m_spotLight->GetDirection();
		}

		/// <summary>
		/// 影響範囲を設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(float range)
		{
			m_spotLight->SetRange(range);
		}
		/// <summary>
		/// 影響範囲を取得
		/// </summary>
		/// <returns></returns>
		float GetRange() const
		{
			return m_spotLight->GetRange();
		}

		/// <summary>
		/// 射出範囲を設定
		/// </summary>
		/// <param name="angle">射出範囲(Degree)</param>
		void SetAngle_Deg(float angle)
		{
			//DegをRadに変換
			angle = Math::DegToRad(angle);
			m_spotLight->SetAngle(angle);
		}
		/// <summary>
		/// 射出範囲を取得
		/// </summary>
		/// <returns>射出範囲</returns>
		const float GetAngle()const
		{
			return m_spotLight->GetAngle();
		}
		/// <summary>
		/// 射出範囲を取得
		/// </summary>
		/// <returns>射出範囲(Degree)</returns>
		const float GetAngle_Deg()const
		{
			//RadをDegに変換してから渡す
			return Math::RadToDeg(m_spotLight->GetAngle());
		}


		/// <summary>
		/// 距離による影響率の累乗数を設定
		/// </summary>
		/// <param name="powParam"></param>
		void SetRangeAffectPowParam(float powParam)
		{
			m_spotLight->SetRangeAffectPowParam(powParam);
		}

		/// <summary>
		/// 角度による累乗数を設定
		/// </summary>
		/// <param name="powParam"></param>
		void SetAngleAffectPowParam(float powParam)
		{
			m_spotLight->SetAngleAffectPowParam(powParam);
		}

		/// <summary>
		/// 生データを取得
		/// </summary>
		/// <returns></returns>
		const SSpotLight& GetRawData() const
		{
			return *m_spotLight;
		}

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update()
		{
			m_spotLight->Update();
		}

		

	private:
		SSpotLight* m_spotLight = nullptr;	//使用するライトのポインタ

	};
}


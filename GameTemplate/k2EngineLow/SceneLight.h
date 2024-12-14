#pragma once

namespace nsK2EngineLow {

	//ディレクションライト構造体
	struct DirectionLight
	{
		Vector3 direction = Vector3::Zero;
		int castShadow = true;
		Vector3 color = Vector3::Zero;
		float pad;
	};

	//ポイントライトの構造体
	struct SPointLight
	{
	private:
		Vector3 position = g_vec3Zero;		//座標
		int isUse = false;					//使用中フラグ
		Vector3 color = g_vec3One;			//ライトのカラー
		float range;						//影響範囲
		Vector3 positionInView;				//カメラ空間での座標
		int pow;							//影響率の累乗数

		//Vector3 position = g_vec3Zero;		//座標
		//int isUse = false;					//使用中フラグ
		//Vector3 color = g_vec3One;			//ライトのカラー
		//float pad1;
		//Vector3 attn = { 1.0f,1.0f,0.0f };	//減衰パラメータ。xに影響範囲、yには影響率に累乗するパラメータ
		//float pad2;
	public:
		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		//座標を取得
		const Vector3& GetPosition() const
		{
			return position;
		}

		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r, g, b });
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return color;
		}

		//範囲を設定
		void SetRange(float range)
		{
			this->range = range;
		}
		//影響範囲を取得
		float GetRange() const
		{
			return range;
		}

		//影響率の累乗数を設定。
		void SetAffectPowParam(float powParam)
		{
			pow = powParam;
		}

		//ポイントライトを使用中にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void Use()
		{
			isUse = true;
		}
		//ポイントライトを未使用にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void UnUse()
		{
			isUse = false;
		}
		//ポイントライトが使用中か調べる
		const int GetUse() const
		{
			return isUse;
		}

		//更新処理
		void Updata();
	};

	//スポットライトの構造体
	struct SSpotLight
	{
	private:
		Vector3 position = g_vec3Zero;	//座標
		int isUse = false;				//使用中フラグ
		Vector3 color = g_vec3One;		//ライトのカラー
		float range = 0.0f;					//影響範囲
		Vector3 direction = g_vec3Down;	//射出方向
		float angle = 0.0f;					//射出範囲
		Vector3 positionInView;			//カメラ空間での座標
		float rangePow;					//距離による影響率の累乗数
		Vector3 directionInView;            // カメラ空間での射出方向。
		float anglePow;					//角度による影響率の累乗数

	public:
		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		//座標を取得
		const Vector3& GetPosition() const
		{
			return position;
		}

		//ライトのカラーを設定
		void SetColor(const Vector3 color)
		{
			this->color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r, g, b });
		}
		//ライトのカラーを取得
		const Vector3& GetColor() const
		{
			return color;
		}

		//射出方向を設定
		void SetDirection(const Vector3& direction)
		{
			this->direction = direction;
			this->direction.Normalize();
		}
		void SetDirection(float x, float y, float z)
		{
			direction.Set(x, y, z);
			direction.Normalize();
		}
		//射出方向を取得
		const Vector3& GetDirection() const
		{
			return direction;
		}

		//スポットライトを使用中にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void Use()
		{
			isUse = true;
		}
		//スポットライトを未使用にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void UnUse()
		{
			isUse = false;
		}
		//スポットライトが使用中か調べる
		const int GetUse() const
		{
			return isUse;
		}


		//影響範囲を設定
		void SetRange(float range)
		{
			this->range = range;
		}
		//影響範囲を取得
		const float GetRange() const
		{
			return range;
		}

		//射出範囲を設定
		void SetAngle(float angle)
		{
			this->angle = angle;
		}
		//射出範囲を取得
		const float GetAngle() const
		{
			return angle;
		}

		//光の距離による影響率に累乗する値を設定
		void SetRangeAffectPowParam(float powParam)
		{
			rangePow = powParam;
		}

		//光の角度による影響率に累乗する値を設定
		void SetAngleAffectPowParam(float powParam)
		{
			anglePow = powParam;
		}

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
	};

	//ライト構造体
	struct Light
	{
		DirectionLight directionalLight;	// ディレクションライト構造体
		SPointLight pointLights[MAX_POINT_LIGHT];	//ポイントライトの配列
		SSpotLight spotLights[MAX_SPOT_LIGHT];	//スポットライトの配列
		Vector3 eyePos = Vector3::Zero;		// 視点の位置
		int numPointLight;					//ポイントライトの数
		Vector3 ambientLight = Vector3::Zero;	//環境光
		int numSpotLight;					//スポットライトの数
		Vector3 eyeDir = Vector3::Zero;		//視線の方向
		float pad3;
	};

	class SceneLight : public Noncopyable
	{
	private:

	public:
		SceneLight();
		~SceneLight();

		//初期化
		void Init();

		//更新処理
		void Update();

		//シーンライトを取得
		Light& GetSceneLight()
		{
			return m_light;
		}

		//ディレクションライトのパラメータを設定
		void SetDirectionLight(int lightNo, Vector3 direction, Vector3 color)
		{
			direction.Normalize();
			m_light.directionalLight.direction = direction;
			m_light.directionalLight.color = color;
		}

		//環境光を設定
		void SetAmbient(Vector3 ambientcolor)
		{
			m_light.ambientLight = ambientcolor;
		}

		/// <summary>
		/// シーンにポイントライトを追加
		/// </summary>
		/// <remark>
		/// この関数で追加したポイントライトは
		/// 不要になったらDeletePointLight関数を使用して削除してください
		/// </remark>
		/// <returns>追加されたポイントライトのアドレス</returns>
		SPointLight* NewPointLight()
		{
			return NewDynamicLight<SPointLight>(m_unusePointLightQueue);
		}

		/// <summary>
		/// シーンにスポットライトを追加
		/// </summary>
		/// <remark>
		/// この関数で追加したスポットライトは
		/// 不要になったらDeletePointLight関数を使用して削除してください
		/// </remark>
		/// <returns>追加されたスポットライトのアドレス</returns>
		SSpotLight* NewSpotLight()
		{
			return NewDynamicLight<SSpotLight>(m_unuseSpotLightQueue);
		}

		/// <summary>
		/// シーンからポイントライトを削除
		/// </summary>
		/// <param name="pointLight">削除するポイントライト</param>
		void DeletePointLight(SPointLight* pointLight)
		{
			DeleteDynamicLight<SPointLight>(pointLight, m_unusePointLightQueue);
		}


		/// <summary>
		/// シーンからスポットライトを削除
		/// </summary>
		/// <param name="spotLight">削除するスポットライト</param>
		void DeleteSpotLight(SSpotLight* spotLight)
		{
			DeleteDynamicLight<SSpotLight>(spotLight, m_unuseSpotLightQueue);
		}

	private:
		/// <summary>
		/// 新しい動的ライトを追加。
		/// </summary>
		/// <typeparam name="TDynamicLight">追加する動的ライトの種類</typeparam>
		/// <typeparam name="TQue">使用する未使用ライトのキューの型</typeparam>
		/// <param name="que">使用する未使用ライトのキュー</param>
		/// <returns>ライトの追加ができなけらばnullptrを、追加できたら追加したライトのポインタを返す</returns>
		template<class TDynamicLight>
		TDynamicLight* NewDynamicLight(std::deque<TDynamicLight*>& que)
		{
			if (que.empty()) {
				//未使用のライトがない
				return nullptr;
			}
			//未使用のライトをキューから取り出す
			TDynamicLight* newPt = que.front();
			//使用中にする
			newPt->Use();
			//取り出した要素を先頭から除去
			que.pop_front();
			return newPt;
		}

		/// <summary>
		/// シーンから動的ライトを削除
		/// </summary>
		/// <param name="pointLight">削除するポイントライト</param>
		template<class TDynamicLight>
		void DeleteDynamicLight(TDynamicLight* light, std::deque<TDynamicLight*>& que)
		{
			if (light != nullptr) {
				//フラグを未使用に変更する
				light->UnUse();
				//未使用リストに追加する
				que.push_back(light);
			}
		}

	private:
		Light m_light;	//シーンライト
		std::deque<SPointLight*> m_unusePointLightQueue;	//未使用のポイントライトのポインタのキュー
		std::deque<SSpotLight*> m_unuseSpotLightQueue;		//未使用のスポットライトのポインタのキュー
	};
}

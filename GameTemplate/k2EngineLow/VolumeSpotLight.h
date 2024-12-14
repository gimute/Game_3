#pragma once
//ボリュームスポット

namespace nsK2EngineLow {

	class VolumeSpotLight : public VolumeLight<SpotLight, SSpotLight>
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="spotLight">ボリュームライト機能を外付けするスポットライト</param>
		void Init(SpotLight& spotLight)
		{
			VolumeLightBase::Init(
				&spotLight,
				"Assets/modelData/preset/VolumeSpotLight.tkm",
				"PSFinal_SpotLight"
			);
		}

		/// <summary>
		/// スポットライトをもとに更新
		/// </summary>
		void Update();

	};
}




#pragma once

#include "VolumeLightBase.h"

namespace nsK2EngineLow {
	class PointLight;

	/// <summary>
	/// モデルベースのボリュームポイントライト
	/// </summary>
	class VolumePointLight : public VolumeLight<PointLight, SPointLight>
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pointLight">ボリュームライト機能を外付けするポイントライト</param>
		void Init(PointLight& pointLight)
		{
			VolumeLightBase::Init(
				&pointLight,
				"Assets/modelData/preset/VolumePointLight.tkm",
				"PSFinal_PointLight"
			);
		}

		/// <summary>
		/// ポイントライトの情報をもとに更新
		/// </summary>
		void Update();
	};
}



#pragma once

#include "VolumeLightBase.h"

namespace nsK2EngineLow {
	class PointLight;

	/// <summary>
	/// ���f���x�[�X�̃{�����[���|�C���g���C�g
	/// </summary>
	class VolumePointLight : public VolumeLight<PointLight, SPointLight>
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pointLight">�{�����[�����C�g�@�\���O�t������|�C���g���C�g</param>
		void Init(PointLight& pointLight)
		{
			VolumeLightBase::Init(
				&pointLight,
				"Assets/modelData/preset/VolumePointLight.tkm",
				"PSFinal_PointLight"
			);
		}

		/// <summary>
		/// �|�C���g���C�g�̏������ƂɍX�V
		/// </summary>
		void Update();
	};
}



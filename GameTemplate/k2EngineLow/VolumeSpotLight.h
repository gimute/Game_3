#pragma once
//�{�����[���X�|�b�g

namespace nsK2EngineLow {

	class VolumeSpotLight : public VolumeLight<SpotLight, SSpotLight>
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="spotLight">�{�����[�����C�g�@�\���O�t������X�|�b�g���C�g</param>
		void Init(SpotLight& spotLight)
		{
			VolumeLightBase::Init(
				&spotLight,
				"Assets/modelData/preset/VolumeSpotLight.tkm",
				"PSFinal_SpotLight"
			);
		}

		/// <summary>
		/// �X�|�b�g���C�g�����ƂɍX�V
		/// </summary>
		void Update();

	};
}




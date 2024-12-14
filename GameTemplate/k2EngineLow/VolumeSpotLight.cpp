#include "k2EngineLowPreCompile.h"
#include "VolumeSpotLight.h"
//�{�����[���X�|�b�g

namespace nsK2EngineLow {

	void VolumeSpotLight::Update()
	{
		//�X�|�b�g���C�g�̏������ƂɃ��[���h�s����X�V����
		//���W
		Vector3 pos = m_lightData->GetPosition();

		//��]
		Quaternion rot;
		rot.SetRotation(g_vec3Back, m_lightData->GetDirection());

		//�g�嗦
		Vector3 scale;
		//z�����̊g�嗦�͉e���͈͂����̂܂܎g��
		scale.z = m_lightData->GetRange();

		//xy�����̊g�嗦��tan(angle��)�ɉe���͈�(���p�O�p�`�̒�ӂ̒����Ƃ��ĂƂ炦��)�������ċ��߂�
		float angle = m_lightData->GetAngle();
		//tan(90��)���Ƃ܂����̂œK���Ɋp�x�𐧌�����
		float xyScale = tan(std::min<float>(Math::PI * 0.49f, angle)) * m_lightData->GetRange();
		scale.x = xyScale;
		scale.y = xyScale;

		//���[���h�s��X�V
		m_modelBack.UpdateWorldMatrix(pos, rot, scale);
		m_modelFront.UpdateWorldMatrix(pos, rot, scale);
	}


}

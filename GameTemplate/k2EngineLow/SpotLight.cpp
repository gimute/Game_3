#include "k2EngineLowPreCompile.h"
#include "SpotLight.h"

namespace nsK2EngineLow {
	SpotLight::~SpotLight()
	{
		//�O���[�o���V�[�����C�g�ƃ����o�ϐ��̃V�[�����C�g��nullptr����Ȃ����
		if (g_sceneLight && m_spotLight)
		{
			//���C�g���폜����
			g_sceneLight->DeleteSpotLight(m_spotLight);
		}
	}

	void SpotLight::Init()
	{
		m_spotLight = g_sceneLight->NewSpotLight();
	}
}

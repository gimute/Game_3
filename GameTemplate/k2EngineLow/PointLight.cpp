#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {
	PointLight::~PointLight()
	{
		//�O���[�o���V�[�����C�g�ƃ����o�ϐ��̃|�C���g���C�g��nullptr����Ȃ����
		if (g_sceneLight && m_pointLight)
		{
			// ���C�g���폜����
			g_sceneLight->DeletePointLight(m_pointLight);
		}
	}

	void PointLight::Init()
	{
		m_pointLight = g_sceneLight->NewPointLight();
	}

}
#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {
	PointLight::~PointLight()
	{
		//グローバルシーンライトとメンバ変数のポイントライトがnullptrじゃなければ
		if (g_sceneLight && m_pointLight)
		{
			// ライトを削除する
			g_sceneLight->DeletePointLight(m_pointLight);
		}
	}

	void PointLight::Init()
	{
		m_pointLight = g_sceneLight->NewPointLight();
	}

}
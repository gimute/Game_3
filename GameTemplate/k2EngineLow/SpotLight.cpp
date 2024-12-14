#include "k2EngineLowPreCompile.h"
#include "SpotLight.h"

namespace nsK2EngineLow {
	SpotLight::~SpotLight()
	{
		//グローバルシーンライトとメンバ変数のシーンライトがnullptrじゃなければ
		if (g_sceneLight && m_spotLight)
		{
			//ライトを削除する
			g_sceneLight->DeleteSpotLight(m_spotLight);
		}
	}

	void SpotLight::Init()
	{
		m_spotLight = g_sceneLight->NewSpotLight();
	}
}

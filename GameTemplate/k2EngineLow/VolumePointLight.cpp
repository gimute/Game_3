#include "k2EngineLowPreCompile.h"
#include "VolumePointLight.h"

//volumeポイント
namespace nsK2EngineLow {
	
	void VolumePointLight::Update()
	{
		//ポイントライトの情報をもとにワールド行列を更新する
		Vector3 pos = m_lightData->GetPosition();
		Vector3 scale;
		scale.x = m_lightData->GetRange();
		scale.y = m_lightData->GetRange();
		scale.z = m_lightData->GetRange();

		m_modelBack.UpdateWorldMatrix(pos, g_quatIdentity, scale);
		m_modelFront.UpdateWorldMatrix(pos, g_quatIdentity, scale);
	}

}
#include "k2EngineLowPreCompile.h"
#include "VolumeSpotLight.h"
//ボリュームスポット

namespace nsK2EngineLow {

	void VolumeSpotLight::Update()
	{
		//スポットライトの情報をもとにワールド行列を更新する
		//座標
		Vector3 pos = m_lightData->GetPosition();

		//回転
		Quaternion rot;
		rot.SetRotation(g_vec3Back, m_lightData->GetDirection());

		//拡大率
		Vector3 scale;
		//z方向の拡大率は影響範囲をそのまま使う
		scale.z = m_lightData->GetRange();

		//xy方向の拡大率はtan(angle°)に影響範囲(直角三角形の底辺の長さとしてとらえる)をかけて求める
		float angle = m_lightData->GetAngle();
		//tan(90°)だとまずいので適当に角度を制限する
		float xyScale = tan(std::min<float>(Math::PI * 0.49f, angle)) * m_lightData->GetRange();
		scale.x = xyScale;
		scale.y = xyScale;

		//ワールド行列更新
		m_modelBack.UpdateWorldMatrix(pos, rot, scale);
		m_modelFront.UpdateWorldMatrix(pos, rot, scale);
	}


}

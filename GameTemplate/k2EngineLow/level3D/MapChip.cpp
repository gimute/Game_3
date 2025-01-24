/*!
 *@brief	マップチップ
 */
#include "k2EngineLowPreCompile.h"
#include "MapChip.h"
#include "Level.h"

namespace nsK2EngineLow {
	MapChip::MapChip(const LevelObjectData& objData, const char* filePath)
	{
		//モデルを用意
		m_modelRender.Init(filePath);
		m_modelRender.SetPosition(objData.position);
		m_modelRender.SetRotation(objData.rotation);
		m_modelRender.SetScale(objData.scale);
		m_modelRender.Update();

		//静的物理オブジェクトを作成。
		m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	}

	void MapChip::Draw(RenderContext& rc)
	{
		m_modelRender.Draw(rc);
	}
}

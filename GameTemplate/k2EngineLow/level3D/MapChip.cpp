/*!
 *@brief	�}�b�v�`�b�v
 */
#include "k2EngineLowPreCompile.h"
#include "MapChip.h"
#include "Level.h"

namespace nsK2EngineLow {
	MapChip::MapChip(const LevelObjectData& objData, const char* filePath)
	{
		//���f����p��
		m_modelRender.Init(filePath);
		m_modelRender.SetPosition(objData.position);
		m_modelRender.SetRotation(objData.rotation);
		m_modelRender.SetScale(objData.scale);
		m_modelRender.Update();

		//�ÓI�����I�u�W�F�N�g���쐬�B
		m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	}

	void MapChip::Draw(RenderContext& rc)
	{
		m_modelRender.Draw(rc);
	}
}

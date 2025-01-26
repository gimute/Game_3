#include "stdafx.h"
#include "BackGround.h"

//バックグラウンド

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	//m_bgModel.Init("Assets/modelData/backGround/dungone/dungone_3.tkm");
	//m_bgModel.Init("Assets/modelData/TestModels/background/backgroundSimayuka.tkm");
	//m_bgModel.Init("Assets/modelData/bg/bg.tkm");
	m_bgModel.Init("Assets/modelData/backGround/stage/stage_7.tkm");
	m_bgModel.SetScale(m_scale);
	m_bgModel.SetPosition(m_position);
	m_bgModel.Update();


	m_PhysicsStaticObject.CreateFromModel(m_bgModel.GetModel(), m_bgModel.GetModel().GetWorldMatrix());
	return true;
}

void BackGround::Update()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_bgModel.Draw(rc);
}
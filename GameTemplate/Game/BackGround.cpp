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
	m_bgModel.Init("Assets/modelData/backGround/stage_2.tkm");
	m_bgModel.SetScale({ 2.0f,2.0f,2.0f });
	m_bgModel.SetPosition({ 0.0f,0.0f,0.0f });
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
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
	m_bgModel.Init("Assets/modelData/TestModels/background/testBackGround.tkm");

	return true;
}

void BackGround::Update()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_bgModel.Draw(rc);
}
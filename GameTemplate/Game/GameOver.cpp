#include "stdafx.h"
#include "GameOver.h"

#include "GameTitle.h"

//ゲームオーバー画面

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

bool GameOver::Start()
{
	m_GameOverSprite.Init("Assets/sprite/outGame/GameOver.DDS", 1600, 900);

	m_GameOverSprite.Update();

	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<GameTitle>(0, "game");

		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_GameOverSprite.Draw(rc);
}

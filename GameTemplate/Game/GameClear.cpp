#include "stdafx.h"
#include "GameClear.h"

#include "GameTitle.h"

//ƒQ[ƒ€ƒNƒŠƒA‰æ–Ê

GameClear::GameClear()
{
}

GameClear::~GameClear()
{
}

bool GameClear::Start()
{
	m_GameClearSprite.Init("Assets/sprite/test/testGameClear.DDS", 1920, 1080);

	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<GameTitle>(0, "game");

		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_GameClearSprite.Draw(rc);
}

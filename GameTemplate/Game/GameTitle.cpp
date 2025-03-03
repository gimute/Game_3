#include "stdafx.h"
#include "GameTitle.h"

#include "Game.h"

//ƒ^ƒCƒgƒ‹‰æ–Ê

GameTitle::GameTitle()
{
}

GameTitle::~GameTitle()
{
}

bool GameTitle::Start()
{
	m_TitleSprite.Init("Assets/sprite/test/TestTitle_2.DDS", 1600, 900);

	return true;
}

void GameTitle::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");

		DeleteGO(this);
	}
}

void GameTitle::Render(RenderContext& rc)
{
	m_TitleSprite.Draw(rc);
}

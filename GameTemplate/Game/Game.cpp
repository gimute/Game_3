#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"

#include "GameTitle.h"
#include "GameClear.h"
#include "GameOver.h"

Game::Game()
{

}

Game::~Game()
{
	//オブジェクトの削除
	DeleteGO(m_player);
	
	if (m_enemy != nullptr)
	{
		DeleteGO(m_enemy);
	}

	DeleteGO(m_gameCamera);
	DeleteGO(m_background);

	//NewGO<GameTitle>(0, "gametitle");
}

bool Game::Start()
{	
	CreateGameObject();

	SoundRegistration();

	m_level.Init("Assets/level/Level_2.tkl",
		[&](LevelObjectData& objData)
		{
			if (objData.ForwardMatchName(L"Stage") == true)
			{
				m_background = NewGO<BackGround>(0, "background");
				m_background->SetPosition(objData.position);
				m_background->SetScale(objData.scale);
				return true;
			}
			else if (objData.ForwardMatchName(L"light") == true)
			{
				m_lightManager.NewPointLight(objData.position, {1.0f,0.8f,0.5f}, 500.0f);
				return true;
			}

			return true;
		});

	g_sceneLight->SetDirectionLight(0, { 0.0f,-1.0f,0.0f }, { 0.3f,0.3f,0.3f });

	return true;
}

void Game::Update()
{
	m_lightManager.Update();

	if (m_enemy != nullptr)
	{
		if (m_enemy->IsDead())
		{
			m_enemy = nullptr;
		}
	}

	GameStateTransition();
	
	GameStateDedicatedpProcessing();

}



void Game::Render(RenderContext& rc)
{

}

void Game::CreateGameObject()
{
	m_enemy = NewGO<Enemy>(0, "enemy");


	m_player = NewGO<Player>(0, "player");

	//m_background = NewGO<BackGround>(0, "background");

	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

}

void Game::SoundRegistration()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/slash.wav");
}

void Game::GameStateTransition()
{
	if (m_player->GetLoseFlag())
	{
		m_gameState = enGameOver;
	}

	if (m_enemy == nullptr)
	{
		m_gameState = enGameClear;
	}
}

void Game::GameStateDedicatedpProcessing()
{
	switch (m_gameState)
	{
	case Game::enGameIdle:
		break;
	case Game::enGameOver:
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		break;
	case Game::enGameClear:
		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
		break;
	default:
		break;
	}
}

#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"


Game::Game()
{

}

Game::~Game()
{

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
				m_lightManager.NewPointLight(objData.position, {1.0f,0.8f,0.5f}, 400.0f);
				return true;
			}

			return true;
		});


	g_sceneLight->SetDirectionLight(0, { 0.0f,-1.0f,1.0f }, { 0.4f,0.4f,0.4f });

	return true;
}

void Game::Update()
{
	m_lightManager.Update();
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

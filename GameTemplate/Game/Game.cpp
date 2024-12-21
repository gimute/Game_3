#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{	
	CreateGameObject();

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Game::Update()
{

}



void Game::Render(RenderContext& rc)
{

}

void Game::CreateGameObject()
{
	m_player = NewGO<Player>(0, "player");

	m_background = NewGO<BackGround>(0, "background");

	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
}

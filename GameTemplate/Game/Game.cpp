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
	DeleteGO(m_gameCamera);
	DeleteGO(m_background);
	DeleteGO(m_enemyManager);
}

bool Game::Start()
{	
	//ゲームオブジェクト生成
	CreateGameObject();
	//ゲームで使用する音声の準備
	SoundRegistration();

	//レベルレンダー
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
				//ポイントライトを設置
				m_lightManager.NewPointLight(objData.position, {1.0f,0.8f,0.5f}, 500.0f);
				return true;
			}

			return true;
		});

	//ディレクションライトを設定
	g_sceneLight->SetDirectionLight(0, { 0.0f,-1.0f,0.0f }, { 0.3f,0.3f,0.3f });

	return true;
}

void Game::Update()
{
	//ライトの更新処理
	m_lightManager.Update();

	//ゲームステート更新
	GameStateTransition();
	//ステートごとの処理
	GameStateDedicatedpProcessing();

}



void Game::Render(RenderContext& rc)
{

}

void Game::CreateGameObject()
{
	//エネミーマネージャー
	m_enemyManager = NewGO<EnemyManager>(0, "enemymanager");
	//エネミーを2体生成
	m_enemyManager->NewGOEnemy({ -20.0f,0.0f,0.0f }, Quaternion::Identity);
	m_enemyManager->NewGOEnemy({ 20.0f,0.0f,0.0f }, Quaternion::Identity);

	//プレイヤー
	m_player = NewGO<Player>(0, "player");
	//エネミーリストをプレイヤーに渡す
	m_player->InitEnemyList(m_enemyManager->GetEnemyList());

	//ゲームカメラ
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

}

void Game::SoundRegistration()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/slash.wav");	//攻撃ヒット時の効果音
}

void Game::GameStateTransition()
{
	//プレイヤーが死んだらゲームオーバー
	if (m_player->GetLoseFlag())
	{
		m_gameState = enGameOver;
	}

	//敵が全て倒されたらゲームクリア
	if (m_enemyManager->GetEnemyList().size() <= 0)
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

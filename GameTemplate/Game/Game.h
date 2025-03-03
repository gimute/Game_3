#pragma once

#include "LightManager.h"


class Player;
class BackGround;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:
	//ゲームステート
	enum GameState
	{
		enGameIdle,		//ゲーム進行中
		enGameOver,		//ゲームオーバー
		enGameClear,	//ゲームクリア
	};

	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	/// <summary>
	/// ゲームオブジェクトの生成
	/// </summary>
	void CreateGameObject();

	//サウンドの登録
	void SoundRegistration();

	//ゲームのステート更新
	void GameStateTransition();

	//ステートごとの専用処理
	void GameStateDedicatedpProcessing();

private:
	GameState m_gameState = enGameIdle;

	Player* m_player;			//プレイヤー
	BackGround* m_background;	//バックグラウンド
	GameCamera* m_gameCamera;	//ゲームカメラ
	Enemy* m_enemy;				//エネミー

	Level m_level;

	LightManager m_lightManager;
};


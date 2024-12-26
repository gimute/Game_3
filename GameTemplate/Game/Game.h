#pragma once

class Player;
class BackGround;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// ゲームオブジェクトの生成
	/// </summary>
	void CreateGameObject();


private:
	Player* m_player;			//プレイヤー
	BackGround* m_background;	//バックグラウンド
	GameCamera* m_gameCamera;	//ゲームカメラ
	Enemy* m_enemy;				//エネミー
};


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
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

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

	SpriteRender m_spRender;
};


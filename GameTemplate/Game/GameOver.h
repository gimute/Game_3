#pragma once

//ゲームオーバー画面
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_GameOverSprite;
};


#pragma once

//タイトル画面
class GameTitle : public IGameObject
{
public:
	GameTitle();
	~GameTitle();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_TitleSprite;
};


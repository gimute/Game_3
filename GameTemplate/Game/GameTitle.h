#pragma once

//ƒ^ƒCƒgƒ‹‰æ–Ê
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


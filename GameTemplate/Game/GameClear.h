#pragma once

//ƒQ[ƒ€ƒNƒŠƒA‰æ–Ê
class GameClear	: public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_GameClearSprite;
};


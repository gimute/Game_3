#pragma once

class Player;
class BackGround;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Player* m_player;
	BackGround* m_background;
};


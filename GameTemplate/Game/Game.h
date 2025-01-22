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
	/// �Q�[���I�u�W�F�N�g�̐���
	/// </summary>
	void CreateGameObject();


private:
	Player* m_player;			//�v���C���[
	BackGround* m_background;	//�o�b�N�O���E���h
	GameCamera* m_gameCamera;	//�Q�[���J����
	Enemy* m_enemy;				//�G�l�~�[

	SpriteRender m_spRender;
};


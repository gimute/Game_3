#pragma once

class Player;
class BackGround;
class GameCamera;

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
	/// �Q�[���I�u�W�F�N�g�̐���
	/// </summary>
	void CreateGameObject();


private:
	Player* m_player;			//�v���C���[
	BackGround* m_background;	//�o�b�N�O���E���h
	GameCamera* m_gameCamera;	//�Q�[���J����
};


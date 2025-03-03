#pragma once

#include "LightManager.h"


class Player;
class BackGround;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:
	//�Q�[���X�e�[�g
	enum GameState
	{
		enGameIdle,		//�Q�[���i�s��
		enGameOver,		//�Q�[���I�[�o�[
		enGameClear,	//�Q�[���N���A
	};

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

	//�T�E���h�̓o�^
	void SoundRegistration();

	//�Q�[���̃X�e�[�g�X�V
	void GameStateTransition();

	//�X�e�[�g���Ƃ̐�p����
	void GameStateDedicatedpProcessing();

private:
	GameState m_gameState = enGameIdle;

	Player* m_player;			//�v���C���[
	BackGround* m_background;	//�o�b�N�O���E���h
	GameCamera* m_gameCamera;	//�Q�[���J����
	Enemy* m_enemy;				//�G�l�~�[

	Level m_level;

	LightManager m_lightManager;
};


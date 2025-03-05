#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"

#include "GameTitle.h"
#include "GameClear.h"
#include "GameOver.h"

Game::Game()
{

}

Game::~Game()
{
	//�I�u�W�F�N�g�̍폜
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_background);
	DeleteGO(m_enemyManager);
}

bool Game::Start()
{	
	//�Q�[���I�u�W�F�N�g����
	CreateGameObject();
	//�Q�[���Ŏg�p���鉹���̏���
	SoundRegistration();

	//���x�������_�[
	m_level.Init("Assets/level/Level_2.tkl",
		[&](LevelObjectData& objData)
		{
			if (objData.ForwardMatchName(L"Stage") == true)
			{
				m_background = NewGO<BackGround>(0, "background");
				m_background->SetPosition(objData.position);
				m_background->SetScale(objData.scale);
				return true;
			}
			else if (objData.ForwardMatchName(L"light") == true)
			{
				//�|�C���g���C�g��ݒu
				m_lightManager.NewPointLight(objData.position, {1.0f,0.8f,0.5f}, 500.0f);
				return true;
			}

			return true;
		});

	//�f�B���N�V�������C�g��ݒ�
	g_sceneLight->SetDirectionLight(0, { 0.0f,-1.0f,0.0f }, { 0.3f,0.3f,0.3f });

	return true;
}

void Game::Update()
{
	//���C�g�̍X�V����
	m_lightManager.Update();

	//�Q�[���X�e�[�g�X�V
	GameStateTransition();
	//�X�e�[�g���Ƃ̏���
	GameStateDedicatedpProcessing();

}



void Game::Render(RenderContext& rc)
{

}

void Game::CreateGameObject()
{
	//�G�l�~�[�}�l�[�W���[
	m_enemyManager = NewGO<EnemyManager>(0, "enemymanager");
	//�G�l�~�[��2�̐���
	m_enemyManager->NewGOEnemy({ -20.0f,0.0f,0.0f }, Quaternion::Identity);
	m_enemyManager->NewGOEnemy({ 20.0f,0.0f,0.0f }, Quaternion::Identity);

	//�v���C���[
	m_player = NewGO<Player>(0, "player");
	//�G�l�~�[���X�g���v���C���[�ɓn��
	m_player->InitEnemyList(m_enemyManager->GetEnemyList());

	//�Q�[���J����
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

}

void Game::SoundRegistration()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/slash.wav");	//�U���q�b�g���̌��ʉ�
}

void Game::GameStateTransition()
{
	//�v���C���[�����񂾂�Q�[���I�[�o�[
	if (m_player->GetLoseFlag())
	{
		m_gameState = enGameOver;
	}

	//�G���S�ē|���ꂽ��Q�[���N���A
	if (m_enemyManager->GetEnemyList().size() <= 0)
	{
		m_gameState = enGameClear;
	}
}

void Game::GameStateDedicatedpProcessing()
{
	switch (m_gameState)
	{
	case Game::enGameIdle:
		break;
	case Game::enGameOver:
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		break;
	case Game::enGameClear:
		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
		break;
	default:
		break;
	}
}

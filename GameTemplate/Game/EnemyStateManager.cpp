#include "stdafx.h"
#include "EnemyStateManager.h"
#include "Player.h"

//�G�l�~�[�X�e�[�g�}�l�[�W���[

void EnemyStateManager::Init(Enemy* enemy)
{
	m_state = &m_stateIdle;
	m_nowState = enEnemyIdle;

	m_enemy = enemy;

	m_player = FindGO<Player>("player");
}

void EnemyStateManager::StateTransition()
{
	//�J�ڂ���X�e�[�g���擾
	EnEnemyState transitionState = m_state->StateTransition();

	//���݂̃X�e�[�g�Ɠ����Ȃ牽�����Ȃ�
	if (m_nowState == transitionState)
	{
		return;
	}
	else
	{
		//�X�e�[�g���؂�ւ��ۂ̏���
		m_state->End(m_enemy);

		//���݂̃X�e�[�g�X�V
		m_nowState = transitionState;


		switch (transitionState)
		{
		case enEnemyIdle:
			m_state = &m_stateIdle;
			m_state->Start(m_enemy);
			break;

		case enEnemyWiteAndSee:
			m_state = &m_stateWaitAndSee;
			m_state->Start(m_enemy);
			break;

		case enEnemyAttackPrepare:
			m_state = &m_stateAttackPrepare;
			m_state->Start(m_enemy);
			break;

		case enEnemyJumpSlash:
			m_state = &m_stateJumpSlash;
			m_state->Start(m_enemy);
			break;

		case enEnemySideSlash:
			m_state = &m_stateSideSlash;
			m_state->Start(m_enemy);
			break;

		case enEnemyReceiveDamage:
			m_state = &m_stateReceiveDamage;
			m_state->Start(m_enemy);
			break;

		case enEnemyDie:
			m_state = &m_stateDie;
			m_state->Start(m_enemy);
			break;

		default:
			break;
		}
	}
	
}

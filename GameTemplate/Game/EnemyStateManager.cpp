#include "stdafx.h"
#include "EnemyStateManager.h"

//�G�l�~�[�X�e�[�g�}�l�[�W���[

void EnemyStateManager::Init(Enemy* enemy)
{
	m_state = &m_stateIdle;
	m_nowState = enenemyIdle;

	m_enemy = enemy;
}

void EnemyStateManager::SetState(EnEnemyState state)
{
	if (m_nowState == state)
	{
		return;
	}
	else
	{
		m_nowState = state;

		switch (state)
		{
		case enenemyIdle:
			m_state = &m_stateIdle;
			break;
		case enenemyWalk:
			break;
		default:
			break;
		}
	}

}
#include "stdafx.h"
#include "EnemyStateManager.h"
#include "Player.h"

//エネミーステートマネージャー

void EnemyStateManager::Init(Enemy* enemy)
{
	m_state = &m_stateIdle;
	m_nowState = enEnemyIdle;

	m_enemy = enemy;

	m_player = FindGO<Player>("player");
}

void EnemyStateManager::StateTransition()
{
	//遷移するステートを取得
	EnEnemyState transitionState = m_state->StateTransition();

	//現在のステートと同じなら何もしない
	if (m_nowState == transitionState)
	{
		return;
	}
	else
	{
		//ステートが切り替わる際の処理
		m_state->End(m_enemy);

		//現在のステート更新
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

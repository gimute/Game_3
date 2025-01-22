#include "stdafx.h"
#include "PlayerStateManager.h"
#include "Player.h"
//ステートマネージャー

void PlayerStateManager::Init(Player* player)
{
	m_state = &m_stateIdle;
	m_nowState = enIdle;

	m_player = player;
}


void PlayerStateManager::SetState(EnPlayerState state)
{
	if (m_nowState == state)
	{
		return;
	}
	else
	{
		m_nowState = state;

		m_state->End(m_player);


		switch (state)
		{
		case enIdle:
			m_state = &m_stateIdle;
			m_state->Start(m_player);
			break;

		case enWalk:
			m_state = &m_stateWalk;
			m_state->Start(m_player);
			break;

		case enAttack:
			m_state = &m_stateAttack;
			m_state->Start(m_player);
			break;

		case enGuard:
			m_state = &m_stateGuard;
			m_state->Start(m_player);
			break;

		case enDodge:
			m_state = &m_stateDodge;
			m_state->Start(m_player);
			break;

		case enReceiveDamage:
			m_state = &m_stateReceiveDamage;
			m_state->Start(m_player);
			break;

		case enJustDodgeAttack:
			m_state = &m_stateJustDodgeAttack;
			m_state->Start(m_player);
			break;

		case enDie:
			m_state = &m_stateDie;
			m_state->Start(m_player);
			break;

		default:
			MessageBox(nullptr, L"プレイヤーのステートが用意できていません", L"エラー", MB_OK);
			break;
		}
	}

	
}



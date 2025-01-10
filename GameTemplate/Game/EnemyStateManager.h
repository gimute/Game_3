#pragma once

#include "EnEnemyState.h"
#include "IEnemyState.h"
#include "EnemyStateIdle.h"
#include "EnemyStateWaitAndSee.h"
#include "EnemyStateAttackPrepare.h"
#include "EnemyStateJumpSlash.h"
#include "EnemyStateSideSlash.h"

class Enemy;
class Player;

//エネミーステートマネージャー
class EnemyStateManager
{
public:
	void Init(Enemy* enemy);

	void Move(Vector3& pos, CharacterController& charaCon)
	{
		m_state->Move(pos, charaCon, m_player);
	}

	void Rotation(Quaternion& rotation)
	{
		m_state->Rotation(rotation);
	}

	void Animation(ModelRender& model)
	{
		m_state->Animation(model);
	}

	void Collision(Vector3 pos, ModelRender& model)
	{
		m_state->Collision(pos, model);
	}

	//ステート遷移処理
	void StateTransition();

private:
	IEnemyState* m_state;

	EnemyStateIdle m_stateIdle;
	EnemyStateWaitAndSee m_stateWaitAndSee;
	EnemyStateAttackPrepare m_stateAttackPrepare;
	EnemyStateJumpSlash m_stateJumpSlash;
	EnemyStateSideSlash m_stateSideSlash;

	EnEnemyState m_nowState;

	

	Enemy* m_enemy;
	Player* m_player;
};


#pragma once

#include "EnEnemyState.h"
#include "IEnemyState.h"
#include "EnemyStateIdle.h"
#include "EnemyStateWaitAndSee.h"
#include "EnemyStateAttackPrepare.h"
#include "EnemyStateJumpSlash.h"
#include "EnemyStateSideSlash.h"
#include "EnemyStateReceiveDamage.h"
#include "EnemyStateDie.h"
#include "EnemyStateGurad.h"

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

	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
	{
		m_state->Animation(model, animeEvent);
	}

	void Collision(Vector3 pos, ModelRender& model, CharacterController& characon)
	{
		m_state->Collision(pos, model, characon);
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
	EnemyStateReceiveDamage m_stateReceiveDamage;
	EnemyStateDie m_stateDie;
	EnemyStateGurad m_stateGurad;

	Enemy* m_enemy;
	Player* m_player;
};


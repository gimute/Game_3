#pragma once

#include "EnEnemyState.h"
#include "IEnemyState.h"
#include "EnemyStateIdle.h"

class Enemy;

//エネミーステートマネージャー
class EnemyStateManager
{
public:
	void Init(Enemy* enemy);

	void Move(Vector3& pos, CharacterController& charaCon)
	{
		m_state->Move(pos, charaCon);
	}

	void Rotation(Quaternion& rotation)
	{
		m_state->Rotation(rotation);
	}

	void PlayAnimation(ModelRender& model)
	{
		m_state->PlayAnimation(model);
	}

	void Collision(Vector3 pos, ModelRender& model)
	{
		m_state->Collision(pos, model);
	}

	EnEnemyState StateTransition()
	{
		return m_state->StateTransition();
	}

	void SetState(EnEnemyState state);

private:
	IEnemyState* m_state;

	EnemyStateIdle m_stateIdle;

	EnEnemyState m_nowState;


	Enemy* m_enemy;

};


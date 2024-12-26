#include "stdafx.h"
#include "EnemyStateIdle.h"

#include "Enemy.h"

//待機ステート

void EnemyStateIdle::PlayAnimation(ModelRender& model)
{
	model.PlayAnimation(Enemy::enAnimationClip_Idle, 0.1f);
}

EnEnemyState EnemyStateIdle::StateTransition()
{
	return enenemyIdle;
}

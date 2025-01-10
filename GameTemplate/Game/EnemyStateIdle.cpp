#include "stdafx.h"
#include "EnemyStateIdle.h"

#include "Enemy.h"
#include "Player.h"

//待機ステート

void EnemyStateIdle::Animation(ModelRender& model)
{
	model.PlayAnimation(Enemy::enAnimationClip_Idle, 0.1f);
}

EnEnemyState EnemyStateIdle::StateTransition()
{


	return enEnemyWiteAndSee;
}

#include "stdafx.h"
#include "EnemyStateIdle.h"

#include "Enemy.h"

//�ҋ@�X�e�[�g

void EnemyStateIdle::PlayAnimation(ModelRender& model)
{
	model.PlayAnimation(Enemy::enAnimationClip_Idle, 0.1f);
}

EnEnemyState EnemyStateIdle::StateTransition()
{
	return enenemyIdle;
}

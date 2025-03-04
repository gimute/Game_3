#include "stdafx.h"
#include "EnemyStateGurad.h"

#include "Enemy.h"

//�U�����K�[�h�����ۂ̃X�e�[�g

void EnemyStateGurad::Start(Enemy* enemy, Player* player)
{
	m_isPlayAnimation = true;
}

void EnemyStateGurad::Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimatinoClip_DamageGuard, 0.1f);
	}
	else
	{
		m_isPlayAnimation = false;
	}
}

EnEnemyState EnemyStateGurad::StateTransition()
{
	if (m_isPlayAnimation)
	{
		return enContinue;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

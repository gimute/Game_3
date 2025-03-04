#include "stdafx.h"
#include "EnemyStateGurad.h"

#include "Enemy.h"

//攻撃をガードした際のステート

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

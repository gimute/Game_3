#include "stdafx.h"
#include "EnemyStateReceiveDamage.h"

#include "Enemy.h"

//ステート

void EnemyStateReceiveDamage::Start(Enemy* enemy)
{
	m_animationPlay = true;
	enemy->DamageProcess();
	if (enemy->GetNowHP() <= 0)
	{
		m_isDeth = true;
	}
}

void EnemyStateReceiveDamage::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_ReceiveDamage, 0.1f);
	}
	else
	{
		m_animationPlay = false;
	}
}



EnEnemyState EnemyStateReceiveDamage::StateTransition()
{
	if (m_isDeth)
	{
		return enEnemyDie;
	}

	if (m_animationPlay)
	{
		return enEnemyReceiveDamage;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

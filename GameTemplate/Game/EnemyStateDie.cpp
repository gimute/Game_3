#include "stdafx.h"
#include "EnemyStateDie.h"

#include "Enemy.h"

void EnemyStateDie::Start(Enemy* enemy)
{
	m_isPlayAnimation = true;
}

void EnemyStateDie::End(Enemy* enemy)
{
	enemy->Delete();
}

void EnemyStateDie::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	if(model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_Backflip, 0.1f);


	}
	else
	{
		m_isPlayAnimation = false;
	}
}

EnEnemyState EnemyStateDie::StateTransition()
{
	if (m_isPlayAnimation)
	{
		return enEnemyDie;
	}
	else
	{
		return enEnemyIdle;
	}

}



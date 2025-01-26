#include "stdafx.h"
#include "EnemyStateReceiveDamage.h"

#include "Enemy.h"

//ステート

void EnemyStateReceiveDamage::Start(Enemy* enemy, Player* player)
{
	m_animationPlay = true;
	enemy->Damage(1.0f);
	if (enemy->GetNowHP() <= 0)
	{
		m_isDeth = true;
	}

	//g_gameTime->SetTimeMulValue(0.0f);
	//hitstop = 3.0f;

	SoundSource* slashSound = NewGO<SoundSource>(0,"slashSound");
	slashSound->Init(0);
	slashSound->SetVolume(0.1f);
	slashSound->Play(false);
}

void EnemyStateReceiveDamage::End(Enemy* enemy)
{
	//g_gameTime->SetTimeMulValue(1.0f);
}

void EnemyStateReceiveDamage::Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_ReceiveDamage, 0.1f);
	}
	else
	{
		m_animationPlay = false;
	}

	/*if (hitstop <= 0.0f)
	{
		g_gameTime->SetTimeMulValue(1.0f);
	}
	else
	{
		hitstop -= 1.0f;
	}*/
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

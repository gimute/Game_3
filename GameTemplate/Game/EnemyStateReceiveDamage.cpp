#include "stdafx.h"
#include "EnemyStateReceiveDamage.h"

#include "Enemy.h"

#include "PlayerParameter.h"

//ステート

void EnemyStateReceiveDamage::Start(Enemy* enemy, Player* player)
{
	m_animationPlay = true;
	enemy->Damage(1.0f);
	if (enemy->GetNowHP() <= 0)
	{
		m_isDeth = true;
	}

	enemy->GetModel()->PlayAnimation(Enemy::enAnimationClip_Idle, 1.0f);

	SoundSource* slashSound = NewGO<SoundSource>(0,"slashSound");
	slashSound->Init(0);
	slashSound->SetVolume(0.1f);
	slashSound->Play(false);

	m_rashAttackHit = false;

}

void EnemyStateReceiveDamage::End(Enemy* enemy)
{

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
}

void EnemyStateReceiveDamage::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//プレイヤーの攻撃コリジョン取得
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(PLAYER_ATTACK_COLLISION_NAME);

	//被ダメージ判定
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->GetAdditionalInformation() == PLAYER_JUSTDODGE_ATTACK_COLLISION_INFORMATION)
		{
			if (collision->IsHit(characon))
			{
				collision->SetIsEnable(false);

				m_rashAttackHit = true;
			}
		}	
	}
}



EnEnemyState EnemyStateReceiveDamage::StateTransition()
{
	if (m_isDeth)
	{
		return enEnemyDie;
	}

	if (m_rashAttackHit)
	{
		return enEnemyReceiveDamage;
	}

	if (m_animationPlay)
	{
		return enContinue;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

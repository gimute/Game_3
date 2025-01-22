#include "stdafx.h"
#include "EnemyStateSideSlash.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

void EnemyStateSideSlash::Start(Enemy* enemy)
{
	m_isPlayAnimation = true;

	enemy->GetModel()->PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);

	//コリジョンの準備
	m_attackCollision = NewGO<CollisionObject>(0);
	m_attackCollision->CreateBox(enemy->GetPosition(), Quaternion::Identity, Vector3(50.0f, 50.0f, 50.0f));
	m_attackCollision->SetName(ENEMY_ATTACK_COLLISION_NAME);
	//横攻撃なので追加情報に横攻撃を設定
	m_attackCollision->SetAdditionalInformation(ENEMY_SIDE_ATTACK_NAME);
	m_attackCollision->SetIsEnableAutoDelete(false);

	//コリジョンを生成するボーンのIDを取得
	m_attackBoneID = enemy->GetModel()->FindBoneID(ENEMY_ATTACK_COLLISION_BONE_NAME);
	//コリジョンのワールド行列を、取得したボーンのワールド行列に設定
	m_attackCollision->SetWorldMatrix(enemy->GetModel()->GetBone(m_attackBoneID)->GetWorldMatrix());

	m_hitFlag = false;

}

void EnemyStateSideSlash::End(Enemy* enemy)
{
	//コリジョンを破棄
	DeleteGO(m_attackCollision);
}

void EnemyStateSideSlash::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_Slash, 0.1f);
	}
	else
	{
		m_isPlayAnimation = false;
	}

	
}

void EnemyStateSideSlash::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//コリジョンのワールド行列を更新
	m_attackCollision->SetWorldMatrix(model.GetBone(m_attackBoneID)->GetWorldMatrix());


	//プレイヤーの攻撃コリジョン取得
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects("player_attack");

	//被ダメージ判定
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->IsHit(characon))
		{
			collision->SetIsEnable(false);

			m_hitFlag = true;
		}
	}
}

EnEnemyState EnemyStateSideSlash::StateTransition()
{
	if (m_hitFlag)
	{
		return enEnemyReceiveDamage;
	}

	if (m_isPlayAnimation)
	{
		return enEnemySideSlash;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

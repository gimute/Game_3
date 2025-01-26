#include "stdafx.h"
#include "EnemyStateSideSlash.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"
#include "PlayerParameter.h"

void EnemyStateSideSlash::Start(Enemy* enemy, Player* player)
{
	m_isPlayAnimation = true;

	enemy->GetModel()->PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);

	//コリジョンを生成するボーンのIDを取得
	m_attackBoneID = enemy->GetModel()->FindBoneID(ENEMY_ATTACK_COLLISION_BONE_NAME);

	m_hitFlag = false;

}

void EnemyStateSideSlash::End(Enemy* enemy)
{
	if (m_isAttackCollisionExistence)
	{
		//コリジョンを破棄
		DeleteGO(m_attackCollision);

		m_isAttackCollisionExistence = false;
	}
}

void EnemyStateSideSlash::Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_Slash, 0.1f);
	}
	else
	{
		m_isPlayAnimation = false;
	}

	switch (animeEvent)
	{
	case enEnemyAnimationEvent_AttackEnd:
		animeEvent = enEnemyAnimationEvent_None;
		//攻撃コリジョンを破棄
		DeleteGO(m_attackCollision);

		m_isAttackCollisionExistence = false;
		break;

	case enEnemyAnimationEvent_AttackStart:
		animeEvent = enEnemyAnimationEvent_None;
		//攻撃コリジョンを用意
		m_attackCollision = NewGO<CollisionObject>(0, "enemyattack");
		m_attackCollision->CreateBox(Vector3::Zero, Quaternion::Identity, ENEMY_ATTACK_COLLISION_SIZE);
		m_attackCollision->SetName(ENEMY_ATTACK_COLLISION_NAME);
		//縦攻撃なので追加情報に縦攻撃を設定
		m_attackCollision->SetAdditionalInformation(ENEMY_SIDE_ATTACK_NAME);
		m_attackCollision->SetIsEnableAutoDelete(false);

		m_isAttackCollisionExistence = true;
		break;

	default:
		animeEvent = enEnemyAnimationEvent_None;
		break;
	}
}

void EnemyStateSideSlash::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//プレイヤーの攻撃コリジョン取得
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(PLAYER_ATTACK_COLLISION_NAME);

	//被ダメージ判定
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->IsHit(characon))
		{
			collision->SetIsEnable(false);

			m_hitFlag = true;
		}
	}

	if (m_isAttackCollisionExistence)
	{
		//コリジョンのワールド行列を更新
		m_attackCollision->SetWorldMatrix(model.GetBone(m_attackBoneID)->GetWorldMatrix());
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
		return enContinue;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

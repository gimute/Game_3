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

	//�R���W�����𐶐�����{�[����ID���擾
	m_attackBoneID = enemy->GetModel()->FindBoneID(ENEMY_ATTACK_COLLISION_BONE_NAME);

	m_hitFlag = false;

}

void EnemyStateSideSlash::End(Enemy* enemy)
{
	if (m_isAttackCollisionExistence)
	{
		//�R���W������j��
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
		//�U���R���W������j��
		DeleteGO(m_attackCollision);

		m_isAttackCollisionExistence = false;
		break;

	case enEnemyAnimationEvent_AttackStart:
		animeEvent = enEnemyAnimationEvent_None;
		//�U���R���W������p��
		m_attackCollision = NewGO<CollisionObject>(0, "enemyattack");
		m_attackCollision->CreateBox(Vector3::Zero, Quaternion::Identity, ENEMY_ATTACK_COLLISION_SIZE);
		m_attackCollision->SetName(ENEMY_ATTACK_COLLISION_NAME);
		//�c�U���Ȃ̂Œǉ����ɏc�U����ݒ�
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
	//�v���C���[�̍U���R���W�����擾
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(PLAYER_ATTACK_COLLISION_NAME);

	//��_���[�W����
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
		//�R���W�����̃��[���h�s����X�V
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

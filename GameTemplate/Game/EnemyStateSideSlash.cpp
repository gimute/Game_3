#include "stdafx.h"
#include "EnemyStateSideSlash.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

void EnemyStateSideSlash::Start(Enemy* enemy)
{
	m_isPlayAnimation = true;

	enemy->GetModel()->PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);

	//�R���W�����̏���
	m_attackCollision = NewGO<CollisionObject>(0);
	m_attackCollision->CreateBox(enemy->GetPosition(), Quaternion::Identity, Vector3(50.0f, 50.0f, 50.0f));
	m_attackCollision->SetName(ENEMY_ATTACK_COLLISION_NAME);
	//���U���Ȃ̂Œǉ����ɉ��U����ݒ�
	m_attackCollision->SetAdditionalInformation(ENEMY_SIDE_ATTACK_NAME);
	m_attackCollision->SetIsEnableAutoDelete(false);

	//�R���W�����𐶐�����{�[����ID���擾
	m_attackBoneID = enemy->GetModel()->FindBoneID(ENEMY_ATTACK_COLLISION_BONE_NAME);
	//�R���W�����̃��[���h�s����A�擾�����{�[���̃��[���h�s��ɐݒ�
	m_attackCollision->SetWorldMatrix(enemy->GetModel()->GetBone(m_attackBoneID)->GetWorldMatrix());

	m_hitFlag = false;

}

void EnemyStateSideSlash::End(Enemy* enemy)
{
	//�R���W������j��
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
	//�R���W�����̃��[���h�s����X�V
	m_attackCollision->SetWorldMatrix(model.GetBone(m_attackBoneID)->GetWorldMatrix());


	//�v���C���[�̍U���R���W�����擾
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects("player_attack");

	//��_���[�W����
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

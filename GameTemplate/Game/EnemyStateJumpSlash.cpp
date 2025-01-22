#include "stdafx.h"
#include "EnemyStateJumpSlash.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

//�X�e�[�g

void EnemyStateJumpSlash::Start(Enemy* enemy)
{
	//�A�j���[�V�����Đ����t���O�̏�����
	m_isPlayAnimation = true;

	enemy->GetModel()->PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);

	//�R���W�����̏���
	m_attackCollision = NewGO<CollisionObject>(0);
	m_attackCollision->CreateBox(enemy->GetPosition(), Quaternion::Identity, Vector3(50.0f, 50.0f, 50.0f));
	m_attackCollision->SetName(ENEMY_ATTACK_COLLISION_NAME);
	//�c�U���Ȃ̂Œǉ����ɏc�U����ݒ�
	m_attackCollision->SetAdditionalInformation(ENEMY_VERTICAL_ATTACK_NAME);
	m_attackCollision->SetIsEnableAutoDelete(false);

	//�R���W�����𐶐�����{�[����ID���擾
	m_attackBoneID = enemy->GetModel()->FindBoneID(ENEMY_ATTACK_COLLISION_BONE_NAME);
	//�R���W�����̃��[���h�s����A�擾�����{�[���̃��[���h�s��ɐݒ�
	m_attackCollision->SetWorldMatrix(enemy->GetModel()->GetBone(m_attackBoneID)->GetWorldMatrix());

	m_hitFlag = false;

}

void EnemyStateJumpSlash::End(Enemy* enemy)
{
	//�R���W������j��
	DeleteGO(m_attackCollision);

}

void EnemyStateJumpSlash::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//�v���C���[�ɋ߂Â�����
	//�ړ��x�N�g�������߂�
	//�v���C���[�Ɍ������x�N�g�������߂�
	Vector3 m_moveVec = player->GetPosition() - position;
	//���łɂ����Ńv���C���[�Ƃ̋������U���͈͓������ׂ�

	m_moveVec.Normalize();
	//�����͕����Ɠ���
	m_moveVec *= ENEMY_WALK_SPEED;
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());
}

void EnemyStateJumpSlash::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);
	}
	else
	{
		m_isPlayAnimation = false;
	}
	
}

void EnemyStateJumpSlash::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
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

EnEnemyState EnemyStateJumpSlash::StateTransition()
{
	if (m_hitFlag)
	{
		return enEnemyReceiveDamage;
	}

	if (m_isPlayAnimation)
	{
		return enEnemyJumpSlash;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

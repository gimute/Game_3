#include "stdafx.h"
#include "EnemyStateAttackPrepare.h"
#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"
#include "PlayerParameter.h"

void EnemyStateAttackPrepare::Start(Enemy* enemy, Player* player)
{
	//�U���t���O��������
	m_attackFlag = false;

	//�����łǂ̍U�������邩���肷��
	m_attackType = EnAttackType(std::rand() % enAttackTypeNum);

	//�q�b�g�t���O��������
	hitFlag = false;

	//�X�e�[�g���Ƃ̏���
	switch (m_attackType)
	{
	case EnemyStateAttackPrepare::enSideSlash:
		m_attackRnge = 100.0f;
		break;
	case EnemyStateAttackPrepare::enJumpSlash:
		m_attackRnge = 200.0f;
		break;
	default:
		break;
	}
}

void EnemyStateAttackPrepare::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//�v���C���[�ɋ߂Â�����
	//�ړ��x�N�g�������߂�
	//�v���C���[�Ɍ������x�N�g�������߂�
	m_moveVec = player->GetPosition() - position;
	//���łɂ����Ńv���C���[�Ƃ̋������U���͈͓������ׂ�
	if (m_attackRnge >= m_moveVec.Length())
	{
		m_attackFlag = true;
	}

	m_moveVec.Normalize();
	m_moveVec *= ENEMY_DASH_SPEED;
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());

}

void EnemyStateAttackPrepare::Rotation(Quaternion& rotation)
{
	//�i�s�����Ɍ�������

	//�ړ��x�N�g�������]�����߂�
	rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));
}

void EnemyStateAttackPrepare::Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
{
	model.PlayAnimation(Enemy::enAnimationClip_Walk, 0.1f);
}

void EnemyStateAttackPrepare::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//�v���C���[�̍U���R���W�����擾
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(PLAYER_ATTACK_COLLISION_NAME);

	//��_���[�W����
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->IsHit(characon))
		{
			collision->SetIsEnable(false);

			hitFlag = true;
		}
	}
}

EnEnemyState EnemyStateAttackPrepare::StateTransition()
{
	if (hitFlag)
	{
		return enEnemyReceiveDamage;
	}

	if (m_attackFlag)
	{
		switch (m_attackType)
		{
		case EnemyStateAttackPrepare::enSideSlash:
			return enEnemySideSlash;
			break;

		case EnemyStateAttackPrepare::enJumpSlash:
			return enEnemyJumpSlash;
			break;

		default:
			return enEnemyIdle;
			break;
		}
	}
	else
	{
		return enContinue;
	}

}

#include "stdafx.h"
#include "EnemyStateAttackPrepare.h"
#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

void EnemyStateAttackPrepare::Start(Enemy* enemy)
{
	//�U���t���O��������
	m_attackFlag = false;

	//�����łǂ̍U�������邩���肷��
	m_attackType = EnAttackType(std::rand() % enAttackTypeNum);

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

void EnemyStateAttackPrepare::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	model.PlayAnimation(Enemy::enAnimationClip_Walk, 0.1f);
}

EnEnemyState EnemyStateAttackPrepare::StateTransition()
{
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
		return enEnemyAttackPrepare;
	}

}

#include "stdafx.h"
#include "EnemyStateWaitAndSee.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"
#include "PlayerParameter.h"

//�l�q��

void EnemyStateWaitAndSee::Start(Enemy* enemy, Player* player)
{
	//m_attackTransitionTimer = 1.0f;
	m_hitFlag = false;
}

void EnemyStateWaitAndSee::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//���v���ړ��̃t���O��turu��false�ōs����������
	if (m_clockwiseFlag == false)
	{
		m_clockwiseTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_clockwiseTimer <= 0.0f)
		{
			//�^�C�}�[�������_���Ȏ��ԂŃ��Z�b�g����
			m_clockwiseTimer = float(std::rand() & 3) + 1.0f;

			m_clockwiseFlag = true;
		}
	}
	else
	{
		m_clockwiseTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_clockwiseTimer <= 0.0f)
		{
			//�^�C�}�[�������_���Ȏ��ԂŃ��Z�b�g����
			m_clockwiseTimer = float(std::rand() & 3) + 1.0f;

			m_clockwiseFlag = false;
		}
	}

	//�ړ��x�N�g�������߂�
	Vector3 moveVec = CalcMoveVec(position, player->GetPosition());

	//���߂��ړ��x�N�g�����g���Ĉړ�
	position = charaCon.Execute(moveVec, g_gameTime->GetFrameDeltaTime());
}

void EnemyStateWaitAndSee::Rotation(Quaternion& rotation)
{
	//��������v���C���[�Ɍ������x�N�g�����g���ăv���C���[�̕�����������
	rotation.SetRotationY(atan2(enemyToPlayer.x, enemyToPlayer.z));
}

void EnemyStateWaitAndSee::Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
{
	switch (m_walkState)
	{
	case enStop:
		model.PlayAnimation(Enemy::enAnimationClip_Idle, 0.1f);
		break;

	case enForward:
		model.PlayAnimation(Enemy::enAnimationClip_Walk, 0.1f);
		break;

	case enBack:
		model.PlayAnimation(Enemy::enAnimationClip_BackWalk, 0.1f);
		break;

	case enm_Clockwise:
		model.PlayAnimation(Enemy::enAnimationClip_LateralMovement_Right, 0.1f);
		break;

	default:
		break;
	}

}

void EnemyStateWaitAndSee::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
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
}

EnEnemyState EnemyStateWaitAndSee::StateTransition()
{
	if (m_hitFlag)
	{
		return enEnemyReceiveDamage;
	}

	m_attackTransitionTimer -= 0.01f;
	if (m_attackTransitionTimer < 0.0f)
	{
		m_attackTransitionTimer = 3.0f;
		return enEnemyAttackPrepare;

	}

	return enEnemyWiteAndSee;
}

Vector3 EnemyStateWaitAndSee::CalcMoveVec(const Vector3 enemyPos, const Vector3 playerPos)
{
	Vector3 moveVec = Vector3::Zero;

	//�v���C���[�Ɍ������x�N�g�������߂�
	enemyToPlayer = playerPos - enemyPos;

	//Y���̒l�͂���Ȃ��̂�0��
	enemyToPlayer.y = 0.0f;

	//�������o���Ă��琳�K��
	float distance = enemyToPlayer.Length();
	enemyToPlayer.Normalize();

	//�v���C���[�Ƃ̋��������ɕۂ��߂̈ړ��x�N�g��
	Vector3 keppSistanceMoveVec;
	if (distance > 310.0f)
	{
		keppSistanceMoveVec = enemyToPlayer;
		m_walkState = enForward;
	}
	else if(distance < 290.0f)
	{
		keppSistanceMoveVec = enemyToPlayer * -1;
		m_walkState = enBack;
	}
	else
	{
		keppSistanceMoveVec = Vector3::Zero;
		m_walkState = enStop;
	}

	//�ړ��x�N�g���ɉ��Z
	moveVec += keppSistanceMoveVec;


	if (m_clockwiseFlag == true)
	{
		//���v���Ƀv���C���[�̎��͂���邽�߂̃x�N�g�������߂�
		//�v���C���[�Ɍ������x�N�g���ɐ����ȃx�N�g�������ɓ��������Ƃŉ~�^���ۂ��Ȃ�
		Vector3 clockwiseVec = { enemyToPlayer.z ,0.0f ,-enemyToPlayer.x };

		//�ړ��x�N�g���ɉ��Z
		moveVec += clockwiseVec;

		m_walkState = enm_Clockwise;
	}

	//���߂��x�N�g���Ɉړ��X�s�[�h����Z����
	moveVec *= ENEMY_GUARDWALK_SPEED;

	return moveVec;
}



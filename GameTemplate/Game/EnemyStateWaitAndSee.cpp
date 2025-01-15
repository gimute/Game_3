#include "stdafx.h"
#include "EnemyStateWaitAndSee.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

//�l�q��

void EnemyStateWaitAndSee::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//�v���C���[�̎������铮������������
	//��Ƀv���C���[�֌������x�N�g�������߂��ꂩ�猩�ĉE�Ɍ������ē����Ώ���ɉ~�^���ɂȂ肻��

	//�v���C���[�Ɍ������x�N�g�������߂�
	enemyToPlayer = player->GetPosition() - position;
	//Y���̒l�͂���Ȃ��̂�0��
	enemyToPlayer.y = 0.0f;

	//������ێ�
	float lenge = enemyToPlayer.Length();

	//���K��
	enemyToPlayer.Normalize();

	//���߂��x�N�g�����E��90�x�񂵂��x�N�g�����ړ��x�N�g���ɑ���
	Vector3 moveVec = { enemyToPlayer.z ,0.0f ,-enemyToPlayer.x };

	if (lenge < 300.0f)
	{
		moveVec += enemyToPlayer * -0.5f;
	}
	else if (lenge == 300.0f)
	{

	}
	else
	{
		moveVec += enemyToPlayer * 0.5f;
	}

	moveVec.Normalize();


	moveVec *= ENEMY_GUARDWALK_SPEED;

	//���߂��ړ��x�N�g�����g���Ĉړ�
	position = charaCon.Execute(moveVec, g_gameTime->GetFrameDeltaTime());
}

void EnemyStateWaitAndSee::Rotation(Quaternion& rotation)
{
	//��������v���C���[�Ɍ������x�N�g�����g���ăv���C���[�̕�����������
	rotation.SetRotationY(atan2(enemyToPlayer.x, enemyToPlayer.z));
}

void EnemyStateWaitAndSee::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	model.PlayAnimation(Enemy::enAnimationClip_LateralMovement_Right, 0.1f);
}

EnEnemyState EnemyStateWaitAndSee::StateTransition()
{
	testTimer -= 0.01f;
	if (testTimer < 0.0f)
	{
		testTimer = 5.0f;
		return enEnemyAttackPrepare;

	}

	return enEnemyWiteAndSee;
}

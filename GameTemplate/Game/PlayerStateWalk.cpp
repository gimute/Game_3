#include "stdafx.h"
#include "PlayerStateWalk.h"
#include "Player.h"

#include "EnemyParameter.h"

void PlayerStateWalk::Start(Player* player)
{
	//�t���O�̃��Z�b�g
	hitFlag = false;
}

void PlayerStateWalk::Move(Vector3& position, CharacterController& charaCon)
{
	m_moveVec = Vector3::Zero;	//�ړ��x�N�g��

	//���X�e�B�b�N�̓��͂��擾
	Vector3 stickL = Vector3::Zero;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	forward.Normalize();
	right.y = 0.0f;
	right.Normalize();

	right *= stickL.x * WalkSpeed;
	forward *= stickL.y * WalkSpeed;

	//�X�e�B�b�N�̓��͂��ړ��x�N�g���ɕϊ�
	m_moveVec += right + forward;

	//�L�����R�����g���č��W���X�V
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());
}

void PlayerStateWalk::Rotation(Quaternion& rotation)
{
	//�i�s�����Ƀv���C���[����������

	//�X�e�B�b�N�̓��͂�������Ώ������΂�
	if (fabsf(g_pad[0]->GetLStickXF()) < 0.001f && fabsf(g_pad[0]->GetLStickYF()) < 0.001f) {
		return;
	}

	//�X�e�B�b�N�̓��͂����]�����߂�
	rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));
}

void PlayerStateWalk::PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	model.SetAnimationSpeed(1.0f);

	model.PlayAnimation(Player::enAnimationClip_Walk, 0.1f);
}

void PlayerStateWalk::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//�G�̍U���R���W�����擾
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_ATTACK_COLLISION_NAME);

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

EnPlayerState PlayerStateWalk::StateTransition()
{
	if (hitFlag)
	{
		return enReceiveDamage;
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		return enAttack;
	}

	if (g_pad[0]->IsPress(enButtonLB1))
	{
		return enGuard;
	}

	if (fabsf(g_pad[0]->GetLStickXF()) < 0.001f && fabsf(g_pad[0]->GetLStickYF()) < 0.001f)
	{
		return enIdle;
	}

	return enWalk;
}

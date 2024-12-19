#include "stdafx.h"
#include "PlayerStateWalk.h"
#include "Player.h"


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

void PlayerStateWalk::AnimationPlay(ModelRender& model) 
{
	model.SetAnimationSpeed(1.0f);

	model.PlayAnimation(Player::enAnimationClip_Walk, 0.1f);
}

EnPlayerState PlayerStateWalk::StateTransition()
{
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

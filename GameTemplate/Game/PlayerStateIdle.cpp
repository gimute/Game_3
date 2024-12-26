#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"


void PlayerStateIdle::PlayAnimation(ModelRender& model)
{
	//�ҋ@���[�V�����Đ�
	model.SetAnimationSpeed(1.0f);
	model.PlayAnimation(Player::enAnimationClip_Idle, 0.1f);
}

EnPlayerState PlayerStateIdle::StateTransition()
{
	//A�{�^���ōU���X�e�[�g
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		return enAttack;
	}

	//LB�{�^���ŃK�[�h�X�e�[�g
	if (g_pad[0]->IsPress(enButtonLB1))
	{
		return enGuard;
	}

	//���X�e�B�b�N�̓��͂�
	if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f || fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
	{
		return enWalk;
	}

	//�ǂ�ɂ�����������Ȃ�������p��
	return enIdle;
}

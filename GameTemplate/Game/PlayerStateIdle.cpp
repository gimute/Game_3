#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"


void PlayerStateIdle::AnimationPlay(ModelRender& model)
{
	model.SetAnimationSpeed(1.0f);

	model.PlayAnimation(Player::enAnimationClip_Idle, 0.1f);
}

EnPlayerState PlayerStateIdle::StateTransition()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		return enAttack;
	}

	if (g_pad[0]->IsPress(enButtonLB1))
	{
		return enGuard;
	}

	if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f || fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
	{
		return enWalk;
	}

	return enIdle;
}

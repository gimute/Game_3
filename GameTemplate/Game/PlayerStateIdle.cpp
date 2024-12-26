#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"


void PlayerStateIdle::PlayAnimation(ModelRender& model)
{
	//待機モーション再生
	model.SetAnimationSpeed(1.0f);
	model.PlayAnimation(Player::enAnimationClip_Idle, 0.1f);
}

EnPlayerState PlayerStateIdle::StateTransition()
{
	//Aボタンで攻撃ステート
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		return enAttack;
	}

	//LBボタンでガードステート
	if (g_pad[0]->IsPress(enButtonLB1))
	{
		return enGuard;
	}

	//左スティックの入力を
	if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f || fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
	{
		return enWalk;
	}

	//どれにも引っかからなかったら継続
	return enIdle;
}

#include "stdafx.h"
#include "PlayerStateReceiveDamage.h"

#include "Player.h"

//ダメージステート

void PlayerStateReceiveDamage::Start(Player* player)
{
	m_animationPlay = true;
}

void PlayerStateReceiveDamage::End(Player* player)
{
}

void PlayerStateReceiveDamage::PlayAnimation(ModelRender& model)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Player::enAnimationClip_Damege, 0.1f);
	}
	else
	{
		m_animationPlay = false;
	}

}

EnPlayerState PlayerStateReceiveDamage::StateTransition()
{
	if (m_animationPlay)
	{
		return enReceiveDamage;
	}
	else
	{
		return enIdle;
	}
}

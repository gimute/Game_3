#include "stdafx.h"
#include "PlayerStateDie.h"

#include "Player.h"

//ステート

void PlayerStateDie::Start(Player* player)
{
	m_isPlayAnimation = true;

}

void PlayerStateDie::End(Player* player)
{
	player->PlayerLose();
}

void PlayerStateDie::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Player::enAnimationClip_Die, 0.1f);
	}
	else
	{
		m_isPlayAnimation = false;
	}
}

EnPlayerState PlayerStateDie::StateTransition()
{
	if (m_isPlayAnimation)
	{
		return enPlayerDie;
	}
	else
	{
		return enPlayerIdle;
	}
}

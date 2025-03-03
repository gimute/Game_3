#include "stdafx.h"
#include "PlayerStateReceiveDamage.h"

#include "Player.h"

//ダメージステート

void PlayerStateReceiveDamage::Start(Player* player)
{
	m_animationPlay = true;
	player->Damage(1.0f);

	m_isDeth = false;
	if (player->GetNowHp() <= 0.0f)
	{
		m_isDeth = true;
	}
}

void PlayerStateReceiveDamage::End(Player* player)
{
}

void PlayerStateReceiveDamage::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Player::enAnimationClip_ReceiveDamage, 0.1f);
	}
	else
	{
		m_animationPlay = false;
	}

}

EnPlayerState PlayerStateReceiveDamage::StateTransition()
{
	if (m_isDeth)
	{
		return enPlayerDie;
	}

	if (m_animationPlay)
	{
		return enPlayerReceiveDamage;
	}
	else
	{
		return enPlayerIdle;
	}
}

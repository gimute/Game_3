#pragma once

#include "EnPlayerState.h"
#include "IPlayerState.h"
#include "PlayerStateIdle.h"
#include "PlayerStateWalk.h"
#include "PlayerStateAttack.h"
#include "PlayerStateGuard.h"
#include "PlayerStateDodge.h"
#include "PlayerStateReceiveDamage.h"
#include "PlayerStateJustDodgeAttack.h"
#include "PlayerStateDie.h"

class Player;

//ステートマネージャー
class PlayerStateManager
{
public:
	void Init(Player* player);


	//移動処理
	void Move(Vector3& position, CharacterController& charaCon)
	{
		m_state->Move(position, charaCon);
	}

	//回転処理
	void Rotation(Quaternion& rotation)
	{
		m_state->Rotation(rotation);
	}

	//アニメーションの再生
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
	{
		m_state->PlayAnimation(model, animeEvent);
	}

	void Collision(Vector3 pos, ModelRender& model, CharacterController& characon)
	{
		m_state->Collision(pos, model, characon);
	}
	
	EnPlayerState StateTransition()
	{
		return m_state->StateTransition();
	}

	void SetState(EnPlayerState state);

private:
	IPlayerState* m_state;

	PlayerStateIdle m_stateIdle;
	PlayerStateWalk m_stateWalk;
	PlayerStateAttack m_stateAttack;
	PlayerStateGuard m_stateGuard;
	PlayerStateDodge m_stateDodge;
	PlayerStateReceiveDamage m_stateReceiveDamage;
	PlayerStateJustDodgeAttack m_stateJustDodgeAttack;
	PlayerStateDie m_stateDie;

	EnPlayerState m_nowState;

	Player* m_player;



};


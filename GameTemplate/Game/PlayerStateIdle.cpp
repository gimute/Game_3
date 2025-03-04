#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"

#include "PlayerParameter.h"
#include "EnemyParameter.h"

void PlayerStateIdle::Start(Player* player)
{
	hitFlag = false;
}

void PlayerStateIdle::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	//待機モーション再生
	model.SetAnimationSpeed(1.0f);
	model.PlayAnimation(Player::enAnimationClip_Idle, 0.2f);
}

void PlayerStateIdle::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//敵の攻撃コリジョン取得
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_ATTACK_COLLISION_NAME);

	//被ダメージ判定
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->IsHit(characon))
		{
			collision->SetIsEnable(false);

			hitFlag = true;
		}
	}
}

EnPlayerState PlayerStateIdle::StateTransition()
{
	//攻撃に当たっていたら被ダメージステート
	if (hitFlag)
	{
		return enPlayerReceiveDamage;
	}

	//Aボタンで攻撃ステート
	if (g_pad[0]->IsTrigger(PLAYER_ATTACK_BUTTON))
	{
		return enPlayerAttack;
	}

	//LBボタンでガードステート
	if (g_pad[0]->IsPress(PLAYER_GUARD_BUTTON))
	{
		return enPlayerGuard;
	}

	//左スティックの入力を
	if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f || fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
	{
		return enPlayerWalk;
	}

	//どれにも引っかからなかったら継続
	return enPlayerIdle;
}

#include "stdafx.h"
#include "PlayerStateWalk.h"
#include "Player.h"

#include "EnemyParameter.h"
#include "PlayerParameter.h"

void PlayerStateWalk::Start(Player* player)
{
	//フラグのリセット
	hitFlag = false;
}

void PlayerStateWalk::Move(Vector3& position, CharacterController& charaCon)
{
	//左スティックの入力を取得
	Vector3 stickL = Vector3::Zero;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	forward.Normalize();
	right.y = 0.0f;
	right.Normalize();

	right *= stickL.x * WALK_SPEED;
	forward *= stickL.y * WALK_SPEED;

	//スティックの入力を移動ベクトルに変換
	m_moveVec = right + forward;

	//キャラコンを使って座標を更新
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());
}

void PlayerStateWalk::Rotation(Quaternion& rotation, const Vector3& position)
{
	//進行方向にプレイヤーを向かせる

	//スティックの入力が無ければ処理を飛ばす
	if (fabsf(g_pad[0]->GetLStickXF()) < 0.001f && fabsf(g_pad[0]->GetLStickYF()) < 0.001f) {
		return;
	}

	//スティックの入力から回転を求める
	rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));
}

void PlayerStateWalk::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	model.SetAnimationSpeed(1.0f);

	model.PlayAnimation(Player::enAnimationClip_Walk, 0.1f);
}

void PlayerStateWalk::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
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

EnPlayerState PlayerStateWalk::StateTransition()
{
	if (hitFlag)
	{
		return enPlayerReceiveDamage;
	}

	if (g_pad[0]->IsPress(PLAYER_RUN_BUTTON))
	{
		return enPlayerRun;
	}

	if (g_pad[0]->IsTrigger(PLAYER_ATTACK_BUTTON))
	{
		return enPlayerAttack;
	}

	if (g_pad[0]->IsPress(PLAYER_GUARD_BUTTON))
	{
		return enPlayerGuard;
	}

	if (fabsf(g_pad[0]->GetLStickXF()) < 0.001f && fabsf(g_pad[0]->GetLStickYF()) < 0.001f)
	{
		return enPlayerIdle;
	}

	return enPlayerWalk;
}

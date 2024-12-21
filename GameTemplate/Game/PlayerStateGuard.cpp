#include "stdafx.h"
#include "PlayerStateGuard.h"
#include "Player.h"

//ステート

void PlayerStateGuard::Start(Player* player)
{
	m_playerForward = Vector3::Front;

	player->GetModel()->GetRotation().Apply(m_playerForward);

	m_guardCollision = NewGO<CollisionObject>(0);

	Vector3 collisionPos = player->GetPosition();
	collisionPos += (m_playerForward * 30.0f) + (Vector3::Up * 50.0f);

	m_guardCollision->CreateBox(collisionPos, Quaternion::Identity, Vector3(70.0f, 150.0f, 30.0f));
	m_guardCollision->SetIsEnableAutoDelete(false);
	m_guardCollision->SetName("playerGuard");

	

}

void PlayerStateGuard::End(Player* player)
{
	DeleteGO(m_guardCollision);
	m_guardCollision = nullptr;
}

void PlayerStateGuard::Move(Vector3& position, CharacterController& charaCon)
{
	Vector3 moveVec = Vector3::Zero;	//移動ベクトル

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

	right *= stickL.x * GuardWalkSpeed;
	forward *= stickL.y * GuardWalkSpeed;

	//スティックの入力を移動ベクトルに変換
	moveVec += right + forward;

	//キャラコンを使って座標を更新
	position = charaCon.Execute(moveVec, g_gameTime->GetFrameDeltaTime());

	moveVec.Normalize();

	m_guardCollision->SetPosition(position + (Vector3::Up * 50.0f) + (m_playerForward * 30.0f));
}

void PlayerStateGuard::Rotation(Quaternion& rotation)
{
	m_guardCollision->SetRotation(rotation);
}

void PlayerStateGuard::AnimationPlay(ModelRender& model)
{
	model.PlayAnimation(Player::enAnimationClip_Guard, 0.1f);
}

EnPlayerState PlayerStateGuard::StateTransition()
{
	/*if (g_pad[0]->IsTrigger(enButtonX))
	{
		return enBackflip;
	}

	if (g_pad[0]->IsTrigger(enButtonY))
	{
		return enSideDodge;
	}*/

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		return enDodge;
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		return enAttack;
	}

	if (g_pad[0]->IsPress(enButtonLB1))
	{
		return enGuard;
	}
	else
	{
		return enIdle;
	}
}

void PlayerStateGuard::Collision(const Vector3& pos, ModelRender& model)
{

}

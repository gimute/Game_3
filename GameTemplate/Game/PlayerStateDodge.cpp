#include "stdafx.h"
#include "PlayerStateDodge.h"

#include "Player.h"
//ステート

void PlayerStateDodge::Start(Player* player)
{
	m_dodgeCollision = NewGO<CollisionObject>(0);

	Vector3 CollisionPos = player->GetPosition();
	CollisionPos += Vector3::Up * 70.0f;

	m_dodgeCollision->CreateBox(CollisionPos, Quaternion::Identity, Vector3(100.0f, 150.0f, 100.0f));
	m_dodgeCollision->SetIsEnableAutoDelete(false);


	Vector3 playerFront = Vector3::Front;
	player->GetModel()->GetRotation().Apply(playerFront);

	InitDodge(playerFront);

	


	m_animationPlay = true;

}

void PlayerStateDodge::InitDodge(const Vector3& playerFront)
{
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();

	//y軸は必要ないので0にして正規化
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();

	Vector3 inCamera_StickVec = (cameraForward * g_pad[0]->GetLStickYF()) + (cameraRight * g_pad[0]->GetLStickXF());

	if (inCamera_StickVec.Dot(playerFront) < -0.5f)
	{
		m_dodgeVec = playerFront * -1 * 100.0f;

		m_dodgeState = enBack;
	}
	else
	{
		float cross = (playerFront.x * inCamera_StickVec.z) - (playerFront.z * inCamera_StickVec.x);

		Quaternion rot;
		

		if (cross < 0.0f)
		{
			m_dodgeVec = playerFront * 100.0f;

			rot.SetRotationDegY(90.0f);
			rot.Apply(m_dodgeVec);

			m_dodgeState = enLeft;
		}
		else
		{
			m_dodgeVec = playerFront * 100.0f;

			rot.SetRotationDegY(-90.0f);
			rot.Apply(m_dodgeVec);

			m_dodgeState = enRight;
		}
		

	}

	//var cross = (int)((dir.X * other.Y) - (dir.Y * other.X)) / 4;
}
//m_moveVec = Vector3::Zero;	//移動ベクトル
//
////左スティックの入力を取得
//Vector3 stickL = Vector3::Zero;
//stickL.x = g_pad[0]->GetLStickXF();
//stickL.y = g_pad[0]->GetLStickYF();
//
//Vector3 forward = g_camera3D->GetForward();
//Vector3 right = g_camera3D->GetRight();
//
//forward.y = 0.0f;
//forward.Normalize();
//right.y = 0.0f;
//right.Normalize();
//
//right *= stickL.x * WalkSpeed;
//forward *= stickL.y * WalkSpeed;
//
////スティックの入力を移動ベクトルに変換
//m_moveVec += right + forward;




void PlayerStateDodge::End(Player* player)
{
	DeleteGO(m_dodgeCollision);
}

void PlayerStateDodge::Move(Vector3& position, CharacterController& charaCon)
{
	position = charaCon.Execute(m_dodgeVec, g_gameTime->GetFrameDeltaTime());
}

void PlayerStateDodge::AnimationPlay(ModelRender& model)
{
	if (model.IsPlayingAnimation())
	{
		switch (m_dodgeState)
		{
		case PlayerStateDodge::enBack:
			model.PlayAnimation(Player::enAnimationClip_Backflip);
			break;
		case PlayerStateDodge::enLeft:
			model.PlayAnimation(Player::enAnimationClip_DodgeLeft);
			break;
		case PlayerStateDodge::enRight:
			model.PlayAnimation(Player::enAnimationClip_DodgeRight);
			break;
		default:
			break;
		}

	}
	else
	{
		m_animationPlay = false;
	}
}

EnPlayerState PlayerStateDodge::StateTransition()
{
	if (m_animationPlay)
	{
		return enDodge;
	}
	else
	{
		return enIdle;
	}

}

void PlayerStateDodge::Collision(const Vector3& pos, ModelRender& model)
{

}

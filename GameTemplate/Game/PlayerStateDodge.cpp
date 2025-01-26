#include "stdafx.h"
#include "PlayerStateDodge.h"

#include "Player.h"
#include "EnemyParameter.h"
//ステート

void PlayerStateDodge::Start(Player* player)
{
	//回避方向の決定
	Vector3 playerFront = Vector3::Front;
	player->GetModel()->GetRotation().Apply(playerFront);

	InitDodge(playerFront);

	//回避コリジョンの生成
	m_dodgeCollision = NewGO<CollisionObject>(0);

	Vector3 CollisionPos = player->GetPosition();
	CollisionPos += Vector3::Up * 70.0f;

	m_dodgeCollision->CreateBox(CollisionPos, Quaternion::Identity, Vector3(100.0f, 150.0f, 100.0f));
	m_dodgeCollision->SetTimeLimit(0.5f);

	//コリジョンの名前を設定する
	switch (m_dodgeState)
	{
	case PlayerStateDodge::enBack:
		//縦回避
		m_dodgeCollision->SetName("verticalAvoidance");
		break;
	case PlayerStateDodge::enLeft:
		//横回避
		m_dodgeCollision->SetName("sideAvoidance");
		break;
	case PlayerStateDodge::enRight:
		//横回避
		m_dodgeCollision->SetName("sideAvoidance");
		break;
	default:
		break;
	}

	player->GetModel()->SetAnimationSpeed(1.0f);

	//フラグのリセット
	m_animationPlay = true;
	m_justDodge = false;
	hitFlag = false;
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
		
		m_dodgeVec = playerFront * 200.0f;

		if (cross < 0.0f)
		{
			rot.SetRotationDegY(90.0f);
			rot.Apply(m_dodgeVec);

			m_dodgeState = enLeft;
		}
		else
		{
			rot.SetRotationDegY(-90.0f);
			rot.Apply(m_dodgeVec);

			m_dodgeState = enRight;
		}
		

	}

}

void PlayerStateDodge::End(Player* player)
{
	g_gameTime->SetTimeMulValue(1.0f);

	//DeleteGO(m_dodgeCollision);
}

void PlayerStateDodge::Move(Vector3& position, CharacterController& charaCon)
{
	if (m_justDodge == true)
	{
		position = charaCon.Execute(m_dodgeVec, g_gameTime->GetFrameDeltaTime() * 2.5f);

	}
	else
	{
		position = charaCon.Execute(m_dodgeVec, g_gameTime->GetFrameDeltaTime());
	}
}

void PlayerStateDodge::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (m_justDodge == true)
	{
		model.SetAnimationSpeed(4.0f);
	}

	if (model.IsPlayingAnimation())
	{
		switch (m_dodgeState)
		{
		case PlayerStateDodge::enBack:
			model.PlayAnimation(Player::enAnimationClip_Backflip);
			break;
		case PlayerStateDodge::enLeft:
			model.PlayAnimation(Player::enAnimationClip_LeftDodge);
			break;
		case PlayerStateDodge::enRight:
			model.PlayAnimation(Player::enAnimationClip_RightDodge);
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

void PlayerStateDodge::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	if (m_dodgeCollision->IsDead())
	{
		return;
	}

	if (m_justDodge == true)
	{
		return;
	}

	//敵の横攻撃コリジョン取得
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_ATTACK_COLLISION_NAME);

	//回避できる攻撃の種類を確認
	const char* avoidable = nullptr;

	switch (m_dodgeState)
	{
	case PlayerStateDodge::enBack:
		//後ろ回避なので横攻撃を回避可能
		avoidable = ENEMY_SIDE_ATTACK_NAME;
		break;

	case PlayerStateDodge::enLeft:
		//横回避なので縦攻撃を回避可能
		avoidable = ENEMY_VERTICAL_ATTACK_NAME;
		break;

	case PlayerStateDodge::enRight:
		//横回避なので縦攻撃を回避可能
		avoidable = ENEMY_VERTICAL_ATTACK_NAME;
		break;

	default:
		break;
	}

	for (CollisionObject* collision : AttackCollisions)
	{
		//回避方向があっていなかったら処理をスキップ
		if (collision->GetAdditionalInformation() != avoidable)
		{
			//被ダメージ判定
			if (collision->IsHit(characon))
			{
				collision->SetIsEnable(false);

				hitFlag = true;
			}

			continue;
		}

		//回避コリジョンに当たっているか判定
		if (collision->IsHit(m_dodgeCollision))
		{
			g_gameTime->SetTimeMulValue(0.2f);
			g_renderingEngine->EnableCenterBlur();
			m_justDodge = true;
		}
		else
		{
			//被ダメージ判定
			if (collision->IsHit(characon))
			{
				collision->SetIsEnable(false);

				hitFlag = true;
			}
		}
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
		if (m_justDodge)
		{
			return enJustDodgeAttack;
		}
		return enIdle;
	}

	if (!m_justDodge)
	{
		if (hitFlag)
		{
			return enReceiveDamage;
		}
	}
}
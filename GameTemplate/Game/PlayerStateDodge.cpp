#include "stdafx.h"
#include "PlayerStateDodge.h"

#include "Player.h"
#include "EnemyParameter.h"
//�X�e�[�g

void PlayerStateDodge::Start(Player* player)
{
	//�������̌���
	Vector3 playerFront = Vector3::Front;
	player->GetModel()->GetRotation().Apply(playerFront);

	InitDodge(playerFront);

	//����R���W�����̐���
	m_dodgeCollision = NewGO<CollisionObject>(0);

	Vector3 CollisionPos = player->GetPosition();
	CollisionPos += Vector3::Up * 70.0f;

	m_dodgeCollision->CreateBox(CollisionPos, Quaternion::Identity, Vector3(100.0f, 150.0f, 100.0f));
	//m_dodgeCollision->SetIsEnableAutoDelete(false);
	m_dodgeCollision->SetTimeLimit(0.3f);

	//�R���W�����̖��O��ݒ肷��
	switch (m_dodgeState)
	{
	case PlayerStateDodge::enBack:
		//�c���
		m_dodgeCollision->SetName("verticalAvoidance");
		break;
	case PlayerStateDodge::enLeft:
		//�����
		m_dodgeCollision->SetName("sideAvoidance");
		break;
	case PlayerStateDodge::enRight:
		//�����
		m_dodgeCollision->SetName("sideAvoidance");
		break;
	default:
		break;
	}

	m_animationPlay = true;

}

void PlayerStateDodge::InitDodge(const Vector3& playerFront)
{
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();

	//y���͕K�v�Ȃ��̂�0�ɂ��Đ��K��
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

}





void PlayerStateDodge::End(Player* player)
{
	g_gameTime->SetTimeMulValue(1.0f);

	//DeleteGO(m_dodgeCollision);
}

void PlayerStateDodge::Move(Vector3& position, CharacterController& charaCon)
{
	position = charaCon.Execute(m_dodgeVec, g_gameTime->GetFrameDeltaTime());
}

void PlayerStateDodge::PlayAnimation(ModelRender& model)
{
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

	{
		//�G�̉��U���R���W�����擾
		const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_SIDE_ATTACK_COLLISION_NAME);

		for (CollisionObject* collision : AttackCollisions)
		{
			//����R���W�����ɓ������Ă��邩����
			if (collision->IsHit(m_dodgeCollision))
			{
				g_gameTime->SetTimeMulValue(0.5f);
				//m_justDodge = true;
			}
		}
	}

	{
		//�G�̏c�U���R���W�����擾
		const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_VERTICAL_ATTACK_COLLISION_NAME);

		for (CollisionObject* collision : AttackCollisions)
		{
			//����R���W�����ɓ������Ă��邩����
			if (collision->IsHit(m_dodgeCollision))
			{
				g_gameTime->SetTimeMulValue(0.5f);

				//m_justDodge = true;
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
		return enIdle;
	}

}
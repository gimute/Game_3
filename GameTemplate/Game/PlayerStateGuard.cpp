#include "stdafx.h"
#include "PlayerStateGuard.h"
#include "Player.h"

#include "EnemyParameter.h"

//�X�e�[�g

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

	AttackGuardFlag = false;
	hitFlag = false;
}

void PlayerStateGuard::End(Player* player)
{
	DeleteGO(m_guardCollision);
	m_guardCollision = nullptr;
}

void PlayerStateGuard::Move(Vector3& position, CharacterController& charaCon)
{
	Vector3 moveVec = Vector3::Zero;	//�ړ��x�N�g��

	//���X�e�B�b�N�̓��͂��擾
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

	//�X�e�B�b�N�̓��͂��ړ��x�N�g���ɕϊ�
	moveVec += right + forward;

	//�L�����R�����g���č��W���X�V
	position = charaCon.Execute(moveVec, g_gameTime->GetFrameDeltaTime());

	moveVec.Normalize();

	m_guardCollision->SetPosition(position + (Vector3::Up * 50.0f) + (m_playerForward * 30.0f));
}

void PlayerStateGuard::Rotation(Quaternion& rotation)
{
	m_guardCollision->SetRotation(rotation);
}

void PlayerStateGuard::PlayAnimation(ModelRender& model)
{
	if (AttackGuardFlag)
	{
		model.PlayAnimation(Player::enAnimatinoClip_DamageGuard, 0.1f);

		if (!model.IsPlayingAnimation())
		{
			AttackGuardFlag = false;
		}
	}
	else
	{
		model.PlayAnimation(Player::enAnimationClip_Guard, 0.1f);
	}
}



void PlayerStateGuard::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	{

		//�G�̍U���R���W�����擾
		const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_SIDE_ATTACK_COLLISION_NAME);

		

		if (GuardCheck(AttackCollisions))
		{
			AttackGuardFlag = true;
		}

		for (CollisionObject* collision : AttackCollisions)
		{
			if (collision->IsHit(characon))
			{
				collision->SetIsEnable(false);

				hitFlag = true;
			}
		}
	}

	{

		//�U���������������m�F
		const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_VERTICAL_ATTACK_COLLISION_NAME);
		if (GuardCheck(AttackCollisions))
		{
			AttackGuardFlag = true;
		}

		for (CollisionObject* collision : AttackCollisions)
		{
			if (collision->IsHit(characon))
			{
				collision->SetIsEnable(false);

				hitFlag = true;
			}
		}
	}
}

bool PlayerStateGuard::GuardCheck(const std::vector<CollisionObject*>& collisions)
{
	for (CollisionObject* collision : collisions)
	{
		if (collision->IsHit(m_guardCollision))
		{
			collision->SetIsEnable(false);
			return true;
		}
	}

	return false;
}

EnPlayerState PlayerStateGuard::StateTransition()
{
	if (hitFlag)
	{
		return enReceiveDamage;
	}

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
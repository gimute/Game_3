#include "stdafx.h"
#include "PlayerStateGuard.h"
#include "Player.h"

#include "PlayerParameter.h"
#include "EnemyParameter.h"
#include "Enemy.h"

//�X�e�[�g

void PlayerStateGuard::Start(Player* player)
{
	//�^�[�Q�b�g�̃G�l�~�[���󂯎��
	m_lockOnEnemy = player->GetTargetEnemy();

	//player->SetEnemyLockOnFlag(true);
	//�v���C���[��G�̕��Ɍ�������
	Vector3 playerToEnemy = m_lockOnEnemy->GetPosition() - player->GetPosition();
	playerToEnemy.y = 0.0f;
	Quaternion rotation;
	rotation.SetRotationY(atan2(playerToEnemy.x, playerToEnemy.z));
	player->SetRotation(rotation);
	

	//�v���C���[�̐��ʃx�N�g�������߂�
	m_playerForward = Vector3::Front;
	rotation.Apply(m_playerForward);

	m_guardCollision = NewGO<CollisionObject>(0);

	Vector3 collisionPos = player->GetPosition();
	collisionPos += (Vector3::Up * PLAYER_GUARD_COLLISION_POS.y) + (m_playerForward * PLAYER_GUARD_COLLISION_POS.z);

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
	//player->SetEnemyLockOnFlag(false);

}

void PlayerStateGuard::Move(Vector3& position, CharacterController& charaCon)
{
	if (AttackGuardFlag)
	{
		return;
	}

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

	//�K�[�h�R���W�����̍��W�X�V
	Vector3 playerToEnemy = m_lockOnEnemy->GetPosition() - position;
	playerToEnemy.y = 0.0f;
	Quaternion rotation;
	rotation.SetRotationY(atan2(playerToEnemy.x, playerToEnemy.z));

	//�v���C���[�̐��ʃx�N�g�������߂�
	m_playerForward = Vector3::Front;
	rotation.Apply(m_playerForward);

	m_guardCollision->SetPosition(position + (Vector3::Up * PLAYER_GUARD_COLLISION_POS.y) + (m_playerForward * PLAYER_GUARD_COLLISION_POS.z));
}

void PlayerStateGuard::Rotation(Quaternion& rotation, const Vector3& position)
{
	//�v���C���[��G�̕��Ɍ�������
	rotation.SetRotationY(atan2(m_playerForward.x, m_playerForward.z));

	m_guardCollision->SetRotation(rotation);
}

void PlayerStateGuard::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (AttackGuardFlag)
	{
		model.PlayAnimation(Player::enAnimatinoClip_DamageGuard, 0.2f);

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
	//�G�̍U���R���W�����擾
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_ATTACK_COLLISION_NAME);

	//�K�[�h����
	if (GuardCheck(AttackCollisions))
	{
		AttackGuardFlag = true;
	}

	//��_���[�W����
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->IsHit(characon))
		{
			collision->SetIsEnable(false);

			hitFlag = true;
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
		return enPlayerReceiveDamage;
	}

	if (AttackGuardFlag)
	{
		return enPlayerGuard;
	}

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		return enPlayerDodge;
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		return enPlayerAttack;
	}

	if (g_pad[0]->IsPress(enButtonLB1))
	{
		return enPlayerGuard;
	}
	else
	{
		return enPlayerIdle;
	}
}
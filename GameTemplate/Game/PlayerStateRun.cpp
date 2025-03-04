#include "stdafx.h"
#include "PlayerStateRun.h"
#include "Player.h"

#include "PlayerParameter.h"
#include "EnemyParameter.h"

//����X�e�[�g

void PlayerStateRun::Start(Player* player)
{
	//�t���O�̃��Z�b�g
	hitFlag = false;
}

void PlayerStateRun::Move(Vector3& position, CharacterController& charaCon)
{
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

	right *= stickL.x * WALK_SPEED * 2.0f;
	forward *= stickL.y * WALK_SPEED * 2.0f;

	//�X�e�B�b�N�̓��͂��ړ��x�N�g���ɕϊ�
	m_moveVec = right + forward;

	//�L�����R�����g���č��W���X�V
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());
}

void PlayerStateRun::Rotation(Quaternion& rotation, const Vector3& position)
{
	//�i�s�����Ƀv���C���[����������

	//�X�e�B�b�N�̓��͂�������Ώ������΂�
	if (fabsf(g_pad[0]->GetLStickXF()) < 0.001f && fabsf(g_pad[0]->GetLStickYF()) < 0.001f) {
		return;
	}

	//�X�e�B�b�N�̓��͂����]�����߂�
	rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));
}

void PlayerStateRun::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	model.SetAnimationSpeed(1.0f);

	model.PlayAnimation(Player::enAnimationClip_Run, 0.1f);
}

void PlayerStateRun::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//�G�̍U���R���W�����擾
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(ENEMY_ATTACK_COLLISION_NAME);

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

EnPlayerState PlayerStateRun::StateTransition()
{
	if (hitFlag)
	{
		return enPlayerReceiveDamage;
	}

	if (g_pad[0]->IsPress(PLAYER_RUN_BUTTON) == false)
	{
		if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f && fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
		{
			return enPlayerWalk;
		}
		else
		{
			return enPlayerIdle;
		}
	}
	else
	{
		return enPlayerRun;
	}
}

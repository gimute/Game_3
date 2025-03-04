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
	//�ҋ@���[�V�����Đ�
	model.SetAnimationSpeed(1.0f);
	model.PlayAnimation(Player::enAnimationClip_Idle, 0.2f);
}

void PlayerStateIdle::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
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

EnPlayerState PlayerStateIdle::StateTransition()
{
	//�U���ɓ������Ă������_���[�W�X�e�[�g
	if (hitFlag)
	{
		return enPlayerReceiveDamage;
	}

	//A�{�^���ōU���X�e�[�g
	if (g_pad[0]->IsTrigger(PLAYER_ATTACK_BUTTON))
	{
		return enPlayerAttack;
	}

	//LB�{�^���ŃK�[�h�X�e�[�g
	if (g_pad[0]->IsPress(PLAYER_GUARD_BUTTON))
	{
		return enPlayerGuard;
	}

	//���X�e�B�b�N�̓��͂�
	if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f || fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
	{
		return enPlayerWalk;
	}

	//�ǂ�ɂ�����������Ȃ�������p��
	return enPlayerIdle;
}

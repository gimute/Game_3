#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"



void PlayerStateAttack::Start(Player* player)
{
	m_animationPlay = true;
}

void PlayerStateAttack::AnimationPlay(ModelRender& model)
{
	if (model.IsPlayingAnimation())
	{
		model.SetAnimationSpeed(1.5f);

		model.PlayAnimation(Player::enAnimationClip_Slash, 0.1f);

	}
	else
	{
		m_animationPlay = false;
	}
}

EnPlayerState PlayerStateAttack::StateTransition()
{
	if (m_animationPlay)
	{
		return enAttack;	
	}
	else
	{
		return enIdle;
	}
	
}

void PlayerStateAttack::Collision(const Vector3& pos, ModelRender& model)
{
	//UŒ‚ƒRƒŠƒWƒ‡ƒ“‚Ì¶¬
	Matrix matrix = model.GetBone(model.FindBoneID(ATTACK_COLLISION_BONE_NAME))->GetWorldMatrix();

	CollisionObject* attackCollisionObject = NewGO<CollisionObject>(0);
	attackCollisionObject->CreateBox(pos, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
	attackCollisionObject->SetWorldMatrix(matrix);
	attackCollisionObject->SetName("player_attack");
}
#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"



void PlayerStateAttack::Start(Player* player)
{
	//アニメーション再生中フラグを初期化
	m_animationPlay = true;

	//攻撃判定コリジョンを生成するボーンのIDを取得
	m_attackBoneID = player->GetModel()->FindBoneID(PLAYER_ATTACK_COLLISION_BONE_NAME);
}

void PlayerStateAttack::PlayAnimation(ModelRender& model)
{
	if (model.IsPlayingAnimation())
	{
		model.SetAnimationSpeed(1.0f);

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

void PlayerStateAttack::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//攻撃コリジョンの生成
	Matrix matrix = model.GetBone(m_attackBoneID)->GetWorldMatrix();

	CollisionObject* attackCollisionObject = NewGO<CollisionObject>(0);
	attackCollisionObject->CreateBox(pos, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
	attackCollisionObject->SetWorldMatrix(matrix);
	attackCollisionObject->SetName("player_attack");
}
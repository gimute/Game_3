#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"

#include "PlayerParameter.h"

void PlayerStateAttack::Start(Player* player)
{
	//アニメーション再生中フラグを初期化
	m_animationPlay = true;

	//攻撃判定コリジョンを生成するボーンのIDを取得
	m_attackBoneID = player->GetModel()->FindBoneID(PLAYER_ATTACK_COLLISION_BONE_NAME);

	
}

void PlayerStateAttack::End(Player* player)
{
	
	bool IsCollisionNull = m_attackCollision == nullptr;
	//攻撃コリジョンが死んでなかったら、破棄する
	if (!IsCollisionNull || !m_attackCollision->IsDead())
	{
		DeleteGO(m_attackCollision);
	}
}

void PlayerStateAttack::PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
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

	switch (animeEvent)
	{
	case enPlayerAnimationEvent_AttackEnd:
		animeEvent = enPlayerAnimationEvent_None;
		//攻撃コリジョンを破棄
		DeleteGO(m_attackCollision);
		break;

	case enPlayerAnimationEvent_AttackStart:
		animeEvent = enPlayerAnimationEvent_None;
		//攻撃コリジョンを用意
		m_attackCollision = NewGO<CollisionObject>(0, "playerattack");
		m_attackCollision->CreateBox(Vector3::Zero, Quaternion::Identity, PLAYER_SOWLD_SIZE);
		m_attackCollision->SetName("player_attack");
		m_attackCollision->SetIsEnableAutoDelete(false);
		break;

	default:
		break;
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
	//攻撃コリジョンが生きてないなら処理を飛ばす
	if (m_attackCollision == nullptr || m_attackCollision->IsDead())
	{
		return;
	}
	//攻撃コリジョンの座標設定
	//攻撃コリジョンを出すボーンのワールド行列を受け取る
	Matrix matrix = model.GetBone(m_attackBoneID)->GetWorldMatrix();
	
	//行列をそのままコリジョンに適応すると手を中心にコリジョンが出てくるのでずらす
	//行列から回転を取得
	Quaternion rotation;
	rotation.SetRotation(matrix);
	//zに1だけ伸びたベクトルに回転を適用して
	Vector3 test = Vector3::AxisZ;
	rotation.Apply(test);
	//そのベクトルを剣の長さの半分倍にする
	test *= PLAYER_SOWLD_SIZE.z / 2.0f;
	//用意したベクトルで行列の座標にあたる数値をずらす
	matrix.m[3][0] += test.x;
	matrix.m[3][1] += test.y;
	matrix.m[3][2] += test.z;

	//完成した行列をコリジョンに適用
	m_attackCollision->SetWorldMatrix(matrix);
}
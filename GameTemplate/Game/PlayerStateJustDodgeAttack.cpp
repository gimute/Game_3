#include "stdafx.h"
#include "PlayerStateJustDodgeAttack.h"

#include "Player.h"
#include "Enemy.h"

#include "PlayerParameter.h"

//ステート

void PlayerStateJustDodgeAttack::Start(Player* player)
{
	g_gameTime->SetTimeMulValue(0.5f);

	player->GetModel()->PlayAnimation(Player::enAnimationClip_Walk, 0.1f);


	m_attackFlowState = enEnemyApproach;

	//攻撃コリジョンを生成するボーンのIDを取得
	m_attackBoneID = player->GetModel()->FindBoneID(PLAYER_ATTACK_COLLISION_BONE_NAME);

	//攻撃コリジョン準備
	m_attackCollision = NewGO<CollisionObject>(0, "playerattack");
	m_attackCollision->CreateBox(player->GetPosition(), Quaternion::Identity, PLAYER_SOWLD_SIZE);
	m_attackCollision->SetName(PLAYER_ATTACK_COLLISION_NAME);
	m_attackCollision->SetAdditionalInformation(PLAYER_JUSTDODGE_ATTACK_COLLISION_INFORMATION);
	m_attackCollision->SetIsEnableAutoDelete(false);

	m_enemy = player->GetTargetEnemy();
}

void PlayerStateJustDodgeAttack::End(Player* player)
{
	DeleteGO(m_attackCollision);

	g_gameTime->SetTimeMulValue(1.0f);

	g_renderingEngine->DisableCenterBlur();

}

void PlayerStateJustDodgeAttack::Move(Vector3& position, CharacterController& charaCon)
{
	if (m_enemy->IsDead() || m_enemy == nullptr)
	{
		m_enemy = nullptr;
		m_attackFlowState = enEnd;
	}
	else
	{
		playerToEnemyVec = m_enemy->GetPosition() - position;
	}

	if (!m_attackFlowState == enEnemyApproach)
	{
		return;
	}

	
	if (playerToEnemyVec.Length() < 110.0f)
	{
		m_attackFlowState = enAttack1;
	}

	playerToEnemyVec.Normalize();
	playerToEnemyVec *= 1000.0f;

	position = charaCon.Execute(playerToEnemyVec, g_gameTime->GetTrueFrameDeltaTime());

	
}

void PlayerStateJustDodgeAttack::Rotation(Quaternion& rotation, const Vector3& position)
{
	//スティックの入力から回転を求める
	playerToEnemyVec.Normalize();
	rotation.SetRotationY(atan2(playerToEnemyVec.x, playerToEnemyVec.z));
}

void PlayerStateJustDodgeAttack::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (!model.IsPlayingAnimation())
	{
		StateOenStep();
	}

	switch (m_attackFlowState)
	{
	case PlayerStateJustDodgeAttack::enEnemyApproach:
		model.PlayAnimation(Player::enAnimationClip_Walk, 0.1f);
		break;

	case PlayerStateJustDodgeAttack::enAttack1:
		model.SetAnimationSpeed(4.0f);
		model.PlayAnimation(Player::enAnimationClip_Slash, 0.1f);
		break;

	case PlayerStateJustDodgeAttack::enAttack2:
		model.SetAnimationSpeed(5.0f);
		model.PlayAnimation(Player::enAnimationClip_JumpSlash, 0.1f);
		break;

	case PlayerStateJustDodgeAttack::enAttack3:
		model.SetAnimationSpeed(4.0f);
		model.PlayAnimation(Player::enAnimationClip_Slash, 0.1f);
		break;

	default:
		break;
	}

	switch (animeEvent)
	{
	case enPlayerAnimationEvent_AttackEnd:
		animeEvent = enPlayerAnimationEvent_None;
		//攻撃コリジョンを停止
		m_attackCollision->SetIsEnable(false);
		break;

	case enPlayerAnimationEvent_AttackStart:
		animeEvent = enPlayerAnimationEvent_None;
		//攻撃コリジョンを復活
		m_attackCollision->SetIsEnable(true);
		break;

	default:
		animeEvent = enPlayerAnimationEvent_None;
		break;
	}
}

void PlayerStateJustDodgeAttack::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
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

void PlayerStateJustDodgeAttack::StateOenStep()
{
	switch (m_attackFlowState)
	{
	case PlayerStateJustDodgeAttack::enEnemyApproach:
		break;
	case PlayerStateJustDodgeAttack::enAttack1:
		m_attackFlowState = enAttack2;
		//攻撃コリジョンを一旦機能停止
		m_attackCollision->SetIsEnable(false);
		break;
	case PlayerStateJustDodgeAttack::enAttack2:
		m_attackFlowState = enAttack3;
		//攻撃コリジョンを復活
		m_attackCollision->SetIsEnable(true);
		break;
	case PlayerStateJustDodgeAttack::enAttack3:
		m_attackFlowState = enEnd;
		break;
	case PlayerStateJustDodgeAttack::enEnd:
		break;
	default:
		break;
	}

}

EnPlayerState PlayerStateJustDodgeAttack::StateTransition()
{
	if (m_attackFlowState == enEnd)
	{
		return enPlayerIdle;
	}
	else
	{
		return enPlayerJustDodgeAttack;
	}
}

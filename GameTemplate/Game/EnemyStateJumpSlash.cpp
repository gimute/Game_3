#include "stdafx.h"
#include "EnemyStateJumpSlash.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

//ステート

void EnemyStateJumpSlash::Start(Enemy* enemy)
{
	//アニメーション再生中フラグの初期化
	m_isPlayAnimation = true;

	enemy->GetModel()->PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);

	//コリジョンの準備
	m_attackCollision = NewGO<CollisionObject>(0);
	m_attackCollision->CreateBox(enemy->GetPosition(), Quaternion::Identity, Vector3(50.0f, 50.0f, 50.0f));
	m_attackCollision->SetName(ENEMY_VERTICAL_ATTACK_COLLISION_NAME);
	m_attackCollision->SetIsEnableAutoDelete(false);

	//コリジョンを生成するボーンのIDを取得
	m_attackBoneID = enemy->GetModel()->FindBoneID(ENEMY_ATTACK_COLLISION_BONE_NAME);
	//コリジョンのワールド行列を、取得したボーンのワールド行列に設定
	m_attackCollision->SetWorldMatrix(enemy->GetModel()->GetBone(m_attackBoneID)->GetWorldMatrix());
}

void EnemyStateJumpSlash::End(Enemy* enemy)
{
	//コリジョンを破棄
	DeleteGO(m_attackCollision);

}

void EnemyStateJumpSlash::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//プレイヤーに近づく処理
	//移動ベクトルを求める
	//プレイヤーに向かうベクトルを求める
	Vector3 m_moveVec = player->GetPosition() - position;
	//ついでにここでプレイヤーとの距離が攻撃範囲内か調べる

	m_moveVec.Normalize();
	//速さは歩きと同じ
	m_moveVec *= ENEMY_WALK_SPEED;
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());
}

void EnemyStateJumpSlash::Animation(ModelRender& model)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Enemy::enAnimationClip_JumpSlash, 0.1f);
	}
	else
	{
		m_isPlayAnimation = false;
	}
	
}

void EnemyStateJumpSlash::Collision(const Vector3& pos, ModelRender& model)
{
	//コリジョンのワールド行列を更新
	m_attackCollision->SetWorldMatrix(model.GetBone(m_attackBoneID)->GetWorldMatrix());
}

EnEnemyState EnemyStateJumpSlash::StateTransition()
{
	if (m_isPlayAnimation)
	{
		return enEnemyJumpSlash;
	}
	else
	{
		return enEnemyWiteAndSee;
	}
}

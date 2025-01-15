#include "stdafx.h"
#include "EnemyStateAttackPrepare.h"
#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

void EnemyStateAttackPrepare::Start(Enemy* enemy)
{
	//攻撃フラグを初期化
	m_attackFlag = false;

	//乱数でどの攻撃をするか決定する
	m_attackType = EnAttackType(std::rand() % enAttackTypeNum);

	//ステートごとの処理
	switch (m_attackType)
	{
	case EnemyStateAttackPrepare::enSideSlash:
		m_attackRnge = 100.0f;
		break;
	case EnemyStateAttackPrepare::enJumpSlash:
		m_attackRnge = 200.0f;
		break;
	default:
		break;
	}
}

void EnemyStateAttackPrepare::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//プレイヤーに近づく処理
	//移動ベクトルを求める
	//プレイヤーに向かうベクトルを求める
	m_moveVec = player->GetPosition() - position;
	//ついでにここでプレイヤーとの距離が攻撃範囲内か調べる
	if (m_attackRnge >= m_moveVec.Length())
	{
		m_attackFlag = true;
	}

	m_moveVec.Normalize();
	m_moveVec *= ENEMY_DASH_SPEED;
	position = charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());

}

void EnemyStateAttackPrepare::Rotation(Quaternion& rotation)
{
	//進行方向に向かせる

	//移動ベクトルから回転を求める
	rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));
}

void EnemyStateAttackPrepare::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	model.PlayAnimation(Enemy::enAnimationClip_Walk, 0.1f);
}

EnEnemyState EnemyStateAttackPrepare::StateTransition()
{
	if (m_attackFlag)
	{
		switch (m_attackType)
		{
		case EnemyStateAttackPrepare::enSideSlash:
			return enEnemySideSlash;
			break;

		case EnemyStateAttackPrepare::enJumpSlash:
			return enEnemyJumpSlash;
			break;

		default:
			return enEnemyIdle;
			break;
		}
	}
	else
	{
		return enEnemyAttackPrepare;
	}

}

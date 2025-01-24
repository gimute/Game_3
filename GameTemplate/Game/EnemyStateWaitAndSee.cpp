#include "stdafx.h"
#include "EnemyStateWaitAndSee.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"
#include "PlayerParameter.h"

//様子見

void EnemyStateWaitAndSee::Start(Enemy* enemy, Player* player)
{
	//m_attackTransitionTimer = 1.0f;
	m_hitFlag = false;
}

void EnemyStateWaitAndSee::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//時計回り移動のフラグをturuとfalseで行き来させる
	if (m_clockwiseFlag == false)
	{
		m_clockwiseTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_clockwiseTimer <= 0.0f)
		{
			//タイマーをランダムな時間でリセットする
			m_clockwiseTimer = float(std::rand() & 3) + 1.0f;

			m_clockwiseFlag = true;
		}
	}
	else
	{
		m_clockwiseTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_clockwiseTimer <= 0.0f)
		{
			//タイマーをランダムな時間でリセットする
			m_clockwiseTimer = float(std::rand() & 3) + 1.0f;

			m_clockwiseFlag = false;
		}
	}

	//移動ベクトルを求める
	Vector3 moveVec = CalcMoveVec(position, player->GetPosition());

	//求めた移動ベクトルを使って移動
	position = charaCon.Execute(moveVec, g_gameTime->GetFrameDeltaTime());
}

void EnemyStateWaitAndSee::Rotation(Quaternion& rotation)
{
	//自分からプレイヤーに向かうベクトルを使ってプレイヤーの方を向かせる
	rotation.SetRotationY(atan2(enemyToPlayer.x, enemyToPlayer.z));
}

void EnemyStateWaitAndSee::Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent)
{
	switch (m_walkState)
	{
	case enStop:
		model.PlayAnimation(Enemy::enAnimationClip_Idle, 0.1f);
		break;

	case enForward:
		model.PlayAnimation(Enemy::enAnimationClip_Walk, 0.1f);
		break;

	case enBack:
		model.PlayAnimation(Enemy::enAnimationClip_BackWalk, 0.1f);
		break;

	case enm_Clockwise:
		model.PlayAnimation(Enemy::enAnimationClip_LateralMovement_Right, 0.1f);
		break;

	default:
		break;
	}

}

void EnemyStateWaitAndSee::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//プレイヤーの攻撃コリジョン取得
	const auto& AttackCollisions = g_collisionObjectManager->FindCollisionObjects(PLAYER_ATTACK_COLLISION_NAME);

	//被ダメージ判定
	for (CollisionObject* collision : AttackCollisions)
	{
		if (collision->IsHit(characon))
		{
			collision->SetIsEnable(false);

			m_hitFlag = true;
		}
	}
}

EnEnemyState EnemyStateWaitAndSee::StateTransition()
{
	if (m_hitFlag)
	{
		return enEnemyReceiveDamage;
	}

	m_attackTransitionTimer -= 0.01f;
	if (m_attackTransitionTimer < 0.0f)
	{
		m_attackTransitionTimer = 3.0f;
		return enEnemyAttackPrepare;

	}

	return enEnemyWiteAndSee;
}

Vector3 EnemyStateWaitAndSee::CalcMoveVec(const Vector3 enemyPos, const Vector3 playerPos)
{
	Vector3 moveVec = Vector3::Zero;

	//プレイヤーに向かうベクトルを求める
	enemyToPlayer = playerPos - enemyPos;

	//Y軸の値はいらないので0に
	enemyToPlayer.y = 0.0f;

	//距離を出してから正規化
	float distance = enemyToPlayer.Length();
	enemyToPlayer.Normalize();

	//プレイヤーとの距離を一定に保つための移動ベクトル
	Vector3 keppSistanceMoveVec;
	if (distance > 310.0f)
	{
		keppSistanceMoveVec = enemyToPlayer;
		m_walkState = enForward;
	}
	else if(distance < 290.0f)
	{
		keppSistanceMoveVec = enemyToPlayer * -1;
		m_walkState = enBack;
	}
	else
	{
		keppSistanceMoveVec = Vector3::Zero;
		m_walkState = enStop;
	}

	//移動ベクトルに加算
	moveVec += keppSistanceMoveVec;


	if (m_clockwiseFlag == true)
	{
		//時計回りにプレイヤーの周囲を回るためのベクトルを求める
		//プレイヤーに向かうベクトルに垂直なベクトル方向に動かすことで円運動ぽくなる
		Vector3 clockwiseVec = { enemyToPlayer.z ,0.0f ,-enemyToPlayer.x };

		//移動ベクトルに加算
		moveVec += clockwiseVec;

		m_walkState = enm_Clockwise;
	}

	//求めたベクトルに移動スピードを乗算する
	moveVec *= ENEMY_GUARDWALK_SPEED;

	return moveVec;
}



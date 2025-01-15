#include "stdafx.h"
#include "EnemyStateWaitAndSee.h"

#include "Enemy.h"
#include "Player.h"

#include "EnemyParameter.h"

//様子見

void EnemyStateWaitAndSee::Move(Vector3& position, CharacterController& charaCon, Player* player)
{
	//プレイヤーの周りを回る動きをさせたい
	//常にプレイヤーへ向かうベクトルを求めそれから見て右に向かって動けば勝手に円運動になりそう

	//プレイヤーに向かうベクトルを求める
	enemyToPlayer = player->GetPosition() - position;
	//Y軸の値はいらないので0に
	enemyToPlayer.y = 0.0f;

	//距離を保持
	float lenge = enemyToPlayer.Length();

	//正規化
	enemyToPlayer.Normalize();

	//求めたベクトルを右に90度回したベクトルを移動ベクトルに足す
	Vector3 moveVec = { enemyToPlayer.z ,0.0f ,-enemyToPlayer.x };

	if (lenge < 300.0f)
	{
		moveVec += enemyToPlayer * -0.5f;
	}
	else if (lenge == 300.0f)
	{

	}
	else
	{
		moveVec += enemyToPlayer * 0.5f;
	}

	moveVec.Normalize();


	moveVec *= ENEMY_GUARDWALK_SPEED;

	//求めた移動ベクトルを使って移動
	position = charaCon.Execute(moveVec, g_gameTime->GetFrameDeltaTime());
}

void EnemyStateWaitAndSee::Rotation(Quaternion& rotation)
{
	//自分からプレイヤーに向かうベクトルを使ってプレイヤーの方を向かせる
	rotation.SetRotationY(atan2(enemyToPlayer.x, enemyToPlayer.z));
}

void EnemyStateWaitAndSee::Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent)
{
	model.PlayAnimation(Enemy::enAnimationClip_LateralMovement_Right, 0.1f);
}

EnEnemyState EnemyStateWaitAndSee::StateTransition()
{
	testTimer -= 0.01f;
	if (testTimer < 0.0f)
	{
		testTimer = 5.0f;
		return enEnemyAttackPrepare;

	}

	return enEnemyWiteAndSee;
}

#pragma once
#include "EnEnemyState.h"

//エネミーステート基底クラス

class Enemy;
class Player;

class IEnemyState
{
public:
	//このステートに遷移する時の処理
	virtual void Start(Enemy* enemy, Player* player) {};

	//他のステートに遷移するときに行う後処理
	virtual void End(Enemy* enemy) {};

	//移動処理
	virtual void Move(Vector3& position, CharacterController& charaCon, Player* player) {};

	//回転処理
	virtual void Rotation(Quaternion& rotation) {};

	//アニメーションの管理
	virtual void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) {};

	//コリジョン
	virtual void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) {};

	//ステート遷移
	virtual EnEnemyState StateTransition() { return enEnemyIdle; };
};


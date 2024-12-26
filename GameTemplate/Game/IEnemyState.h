#pragma once
#include "EnEnemyState.h"

//エネミーステート基底クラス

class Enemy;

class IEnemyState
{
public:
	//このステートに遷移する時の処理
	virtual void Start(Enemy* enemy) {};

	//他のステートに遷移するときに行う後処理
	virtual void End(Enemy* enemy) {};

	//移動処理
	virtual void Move(Vector3& position, CharacterController& charaCon) {};

	//回転処理
	virtual void Rotation(Quaternion& rotation) {};

	//アニメーションの再生
	virtual void PlayAnimation(ModelRender& model) {};

	//コリジョン
	virtual void Collision(Vector3 pos, ModelRender& model) {};

	//ステート遷移
	virtual EnEnemyState StateTransition() { return enenemyIdle; };
};


#pragma once
#include "IEnemyState.h"

/// <summary>
/// 攻撃準備ステート
/// </summary>
/// <remark>
/// どの攻撃を行うかの決定、その攻撃が届く距離まで近づく処理を行う
/// </remark>
class EnemyStateAttackPrepare : public IEnemyState
{
public:
	//攻撃の種類
	enum EnAttackType
	{
		enSideSlash,	//横切り
		enJumpSlash,	//ジャンプ切り
		enAttackTypeNum	//攻撃の種類の数
	};

	//このステートに遷移する時の処理
	void Start(Enemy* enemy, Player* player) override;

	//移動処理
	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	//回転処理
	void Rotation(Quaternion& rotation) override;

	//アニメーションの再生
	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	//コリジョン
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	//ステート遷移
	EnEnemyState StateTransition() override;

private:
	float m_attackRnge;	//攻撃の届く範囲

	EnAttackType m_attackType;

	Vector3 m_moveVec;

	bool m_attackFlag = false;	//攻撃するか

	bool hitFlag = false;		//被ダメージフラグ

};


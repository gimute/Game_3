#pragma once
#include "IEnemyState.h"

enum EnWalkState {
	enStop,
	enForward,
	enBack,
	enm_Clockwise,
};

//様子見ステート
class EnemyStateWaitAndSee : public IEnemyState
{
public:
	void Start(Enemy* enemy, Player* player) override;

	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	void Rotation(Quaternion& rotation) override;

	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	EnEnemyState StateTransition() override;

private:
	Vector3 CalcMoveVec(const Vector3 enemyPos, const Vector3 playerPos);

private:
	Vector3 enemyToPlayer = Vector3::Zero;

	float m_attackTransitionTimer = 3.0f;

	bool m_hitFlag = false;		//被ダメージフラグ
	bool m_guradFlag = false;	//ガードフラグ

	EnWalkState m_walkState = enStop;

	float m_clockwiseTimer = 1.0f;	//プレイヤーの周囲を回る時間を管理するタイマー
	bool m_clockwiseFlag = false;	//プレイヤーの周囲を回るフラグ
};


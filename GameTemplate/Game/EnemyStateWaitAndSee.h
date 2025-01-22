#pragma once
#include "IEnemyState.h"


//様子見ステート
class EnemyStateWaitAndSee : public IEnemyState
{
public:
	void Start(Enemy* enemy) override;

	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	void Rotation(Quaternion& rotation) override;

	void Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent) override;

	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	EnEnemyState StateTransition() override;

private:
	Vector3 enemyToPlayer = Vector3::Zero;

	float testTimer = 3.0f;

	bool m_hitFlag = false;		//被ダメージフラグ

};


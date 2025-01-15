#pragma once
#include "IEnemyState.h"


//様子見ステート
class EnemyStateWaitAndSee : public IEnemyState
{
public:
	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	void Rotation(Quaternion& rotation) override;

	void Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent) override;

	EnEnemyState StateTransition() override;

private:
	Vector3 enemyToPlayer = Vector3::Zero;

	float testTimer = 5.0f;
};


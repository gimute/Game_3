#pragma once
#include "IEnemyState.h"

//被ダメージステート
class EnemyStateReceiveDamage : public IEnemyState
{
public:
	void Start(Enemy* enemy, Player* player) override;
	void End(Enemy* enemy) override;

	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	EnEnemyState StateTransition() override;

private:
	bool m_animationPlay = true;	//アニメーション再生中フラグ

	bool m_isDeth = false;	//死亡フラグ

	float hitstop = 3.0f;
};


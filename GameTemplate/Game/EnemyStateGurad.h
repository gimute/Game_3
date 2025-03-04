#pragma once
#include "IEnemyState.h"

class EnemyStateGurad : public IEnemyState
{
public:
	void Start(Enemy* enemy, Player* player) override;
	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;
	EnEnemyState StateTransition() override;

private:
	bool m_isPlayAnimation = true;	//アニメーション再生中か


};


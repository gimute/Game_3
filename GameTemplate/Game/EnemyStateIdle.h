#pragma once
#include "EnEnemyState.h"
#include "IEnemyState.h"

//待機ステート
class EnemyStateIdle : public IEnemyState
{
	void Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent) override;
	EnEnemyState StateTransition() override;

};


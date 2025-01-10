#pragma once
#include "EnEnemyState.h"
#include "IEnemyState.h"

//待機ステート
class EnemyStateIdle : public IEnemyState
{
	void Animation(ModelRender& model) override;
	EnEnemyState StateTransition() override;

};


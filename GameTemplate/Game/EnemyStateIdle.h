#pragma once
#include "EnEnemyState.h"
#include "IEnemyState.h"

//�ҋ@�X�e�[�g
class EnemyStateIdle : public IEnemyState
{
	void Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent) override;
	EnEnemyState StateTransition() override;

};


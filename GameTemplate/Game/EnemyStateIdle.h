#pragma once
#include "EnEnemyState.h"
#include "IEnemyState.h"

//�ҋ@�X�e�[�g
class EnemyStateIdle : public IEnemyState
{
	void Animation(ModelRender& model) override;
	EnEnemyState StateTransition() override;

};


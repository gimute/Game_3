#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"


//�������삪�������̃v���C���[�X�e�[�g
class PlayerStateIdle : public IPlayerState
{
public:

	void PlayAnimation(ModelRender& model) override;
	EnPlayerState StateTransition() override;


};


#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"


//何も操作が無い時のプレイヤーステート
class PlayerStateIdle : public IPlayerState
{
public:
	void AnimationPlay(ModelRender& model) override;
	EnPlayerState StateTransition() override;


};


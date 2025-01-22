#pragma once
#include "IPlayerState.h"

//被ダメージステート
class PlayerStateReceiveDamage : public IPlayerState
{
public:
	void Start(Player* player) override;
	void End(Player* player) override;

	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;

private:
	bool m_animationPlay = true;	//アニメーション再生中フラグ
	bool m_isDeth = false;	//しぼうステート

};


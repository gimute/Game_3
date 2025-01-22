#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"


//何もしていない時のプレイヤーステート
class PlayerStateIdle : public IPlayerState
{
public:
	void Start(Player* player) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;
	EnPlayerState StateTransition() override;

private:
	bool hitFlag = false;		//被ダメージフラグ
};


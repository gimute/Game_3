#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"

namespace {
	const float WalkSpeed = 150.0f;
}

//歩き中のプレイヤーステート
class PlayerStateWalk : public IPlayerState
{
public:
	void Start(Player* player)override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void Rotation(Quaternion& rotation) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;
	EnPlayerState StateTransition() override;

private:
	Vector3 m_moveVec = Vector3::Zero;
	bool hitFlag = false;		//被ダメージフラグ
};


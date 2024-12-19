#pragma once
#include "IPlayerState.h"

namespace {
	const float GuardWalkSpeed = 100.0f;
}

//ガードステート
class PlayerStateGuard : public IPlayerState
{
public:

	void Start(Player* player) override;
	void End(Player* player) override;

	void Move(Vector3& position, CharacterController& charaCon) override;
	void Rotation(Quaternion& rotation) override;
	void AnimationPlay(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model) override;

private:
	CollisionObject* m_guardCollision;
	Vector3 m_playerForward = Vector3::Front;
};


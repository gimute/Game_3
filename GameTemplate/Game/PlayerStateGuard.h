#pragma once
#include "IPlayerState.h"

namespace {
	const float GuardWalkSpeed = 100.0f;
}

class Enemy;

//�K�[�h�X�e�[�g
class PlayerStateGuard : public IPlayerState
{
public:
	void Start(Player* player) override;
	void End(Player* player) override;

	void Move(Vector3& position, CharacterController& charaCon) override;
	void Rotation(Quaternion& rotation, const Vector3& position) override;
	void Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

private:
	bool GuardCheck(const std::vector<CollisionObject*>& collisions);

private:
	CollisionObject* m_guardCollision;
	Vector3 m_playerForward = Vector3::Front;

	bool AttackGuardFlag = false;

	bool hitFlag = false;

	Enemy* m_lockOnEnemy;
};


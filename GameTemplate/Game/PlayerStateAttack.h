#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"

namespace {
	const wchar_t* ATTACK_COLLISION_BONE_NAME = L"mixamorig:RightHandMiddle1";
}

//アタックステート
class PlayerStateAttack : public IPlayerState
{
public:

	void Start(Player* player)override;
	void PlayAnimation(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model) override;


private:
	bool m_animationPlay = true;
};


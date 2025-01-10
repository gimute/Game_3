#pragma once
#include "IPlayerState.h"

//�W���X�g����X�e�[�g
class PlayerStateJastDodge : public IPlayerState
{
public:
	void Start(Player* player) override;
	void End(Player* player) override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void PlayAnimation(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

private:
};


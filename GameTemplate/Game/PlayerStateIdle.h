#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"


//�������Ă��Ȃ����̃v���C���[�X�e�[�g
class PlayerStateIdle : public IPlayerState
{
public:
	void Start(Player* player) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;
	EnPlayerState StateTransition() override;

private:
	bool hitFlag = false;		//��_���[�W�t���O
};


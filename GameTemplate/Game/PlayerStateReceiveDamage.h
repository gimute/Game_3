#pragma once
#include "IPlayerState.h"

//��_���[�W�X�e�[�g
class PlayerStateReceiveDamage : public IPlayerState
{
public:
	void Start(Player* player) override;
	void End(Player* player) override;

	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;

private:
	bool m_animationPlay = true;	//�A�j���[�V�����Đ����t���O
	bool m_isDeth = false;	//���ڂ��X�e�[�g

};


#pragma once
#include "IPlayerState.h"

//���ڂ��X�e�[�g
class PlayerStateDie : public IPlayerState
{
public:
	void Start(Player* player) override;
	void End(Player* player) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;

private:
	bool m_isPlayAnimation = true;	//�A�j���[�V�����Đ�����

};


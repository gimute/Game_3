#pragma once
#include "IEnemyState.h"

//��_���[�W�X�e�[�g
class EnemyStateReceiveDamage : public IEnemyState
{
public:
	void Start(Enemy* enemy, Player* player) override;
	void End(Enemy* enemy) override;

	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	EnEnemyState StateTransition() override;

private:
	bool m_animationPlay = true;	//�A�j���[�V�����Đ����t���O

	bool m_isDeth = false;	//���S�t���O

	float hitstop = 3.0f;
};


#pragma once
#include "IPlayerState.h"

//����X�e�[�g
class PlayerStateDodge : public IPlayerState
{
	enum EnDodgeState
	{
		enBack,
		enLeft,
		enRight
	};

public:
	void Start(Player* player) override;
	void End(Player* player) override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void AnimationPlay(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model) override;

private:
	//�������̃X�e�[�g�����肷��֐�
	void InitDodge(const Vector3& playerFront);

	EnDodgeState m_dodgeState;		//�������X�e�[�g
	bool m_animationPlay = true;	//�A�j���[�V�������Đ�����
	CollisionObject* m_dodgeCollision;	//��𔻒�p�R���W����
	Vector3 m_dodgeVec;	//����x�N�g��

};


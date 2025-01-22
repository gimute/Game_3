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
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

private:
	//�������̃x�N�g���ƃX�e�[�g�����肷��֐�
	void InitDodge(const Vector3& playerFront);


private:
	EnDodgeState m_dodgeState;		//�������X�e�[�g
	bool m_animationPlay = true;	//�A�j���[�V�������Đ�����
	CollisionObject* m_dodgeCollision;	//��𔻒�p�R���W����
	Vector3 m_dodgeVec;	//����x�N�g��

	bool m_justDodge = false;	//�W���X�g����t���O
	bool hitFlag = false;		//��_���[�W�t���O
};


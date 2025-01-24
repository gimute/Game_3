#pragma once
#include "IPlayerState.h"

//�A�^�b�N�X�e�[�g
class PlayerStateAttack : public IPlayerState
{
public:

	void Start(Player* player)override;
	void End(Player* player)override;
	void Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;


private:
	bool m_animationPlay = true;	//�A�j���[�V�����Đ����t���O
	int m_attackBoneID;		//�U���R���W�����𐶐�����{�[����ID

	CollisionObject* m_attackCollision;	//�U���R���W����

	bool hitFlag = false;		//��_���[�W�t���O
	bool m_isAttackCollisionExistence = false;	//�U���R���W���������݂��Ă��邩

};


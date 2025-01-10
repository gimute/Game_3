#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"

namespace {
	const wchar_t* PLAYER_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //�U������R���W�����𐶐�����{�[���̖��O
}

//�A�^�b�N�X�e�[�g
class PlayerStateAttack : public IPlayerState
{
public:

	void Start(Player* player)override;
	void PlayAnimation(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;


private:
	bool m_animationPlay = true;	//�A�j���[�V�����Đ����t���O
	int m_attackBoneID;		//�U������R���W�����𐶐�����{�[����ID
};


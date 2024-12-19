#pragma once

#include "EnPlayerState.h"


//�v���C���[�X�e�[�g�̊��N���X

// �X�e�[�g�p�^�[���H������Ă݂�
// �����̗������ƁA�X�e�[�g�������炩�̃I�u�W�F�N�g(����̓v���C���[)�̏������X�e�[�g���ƂɃN���X�ɂ��ĕ����āA
// ���̏������|�����[�t�B�Y���I�Ȃ���ŁA�I�u�W�F�N�g�Ɏ�������X�e�[�g�N���X���Ƃ������Ђ���������ւ���`�ŃR�[�h���������ƁA�݂����ȃC���[�W
//  
// �X�e�[�g���Ƃ̏����𕪂��ď����̂ł��ꂼ��̃X�e�[�g�łǂ��������������Ă�̂��c�����₷��
// �V�����X�e�[�g��ǉ����鎞�ɑ��̃X�e�[�g�̏����Ƃ�������ɂȂ����肹���ǉ����₷��(if���Ƃ��̕��򏈗��Ő��䂷��Ƃ߂�����킩��ɂ����Ȃ�)

class Player;

class IPlayerState
{
public:
	//�X�e�[�g�ɑJ�ڂ���Ƃ��ɍs������
	virtual void Start(Player* player) {};
	//���̃X�e�[�g�ɑJ�ڂ���Ƃ��ɍs������
	virtual void End(Player* player) {};

	//�ړ�����
	virtual void Move(Vector3& position, CharacterController& charaCon) {};
	//��]����
	virtual void Rotation(Quaternion& rotation) {};
	//�A�j���[�V�����̍Đ�
	virtual void AnimationPlay(ModelRender& model) {};
	//�X�e�[�g�J��
	virtual EnPlayerState StateTransition() { return enIdle; };
	//�����蔻�菈��
	virtual void Collision(const Vector3& position, ModelRender& model) {};

};


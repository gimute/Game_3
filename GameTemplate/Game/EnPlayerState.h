#pragma once

//�v���C���[�X�e�[�g

enum EnPlayerState {
	enIdle,		//�ҋ@
	enWalk,		//����
	enAttack,	//�U��
	enGuard,	//�K�[�h
	enDodge,		//���
	enReceiveDamage,	//��_���[�W
	enJustDodgeAttack,	//�W���X�g�����̃��b�V���U��
	enDie,		//���ڂ�
};

//�A�j���[�V�����C�x���g
enum EnPlayerAnimationEvent {
	enPlayerAnimationEvent_AttackStart,
	enPlayerAnimationEvent_AttackEnd,
	enPlayerAnimationEvent_None
};
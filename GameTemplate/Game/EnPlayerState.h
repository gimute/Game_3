#pragma once

//�v���C���[�X�e�[�g

enum EnPlayerState {
	enPlayerIdle,		//�ҋ@
	enPlayerWalk,		//����
	enPlayerAttack,	//�U��
	enPlayerGuard,	//�K�[�h
	enPlayerDodge,		//���
	enPlayerReceiveDamage,	//��_���[�W
	enPlayerJustDodgeAttack,	//�W���X�g�����̃��b�V���U��
	enPlayerDie,		//���ڂ�
};

//�A�j���[�V�����C�x���g
enum EnPlayerAnimationEvent {
	enPlayerAnimationEvent_AttackStart,
	enPlayerAnimationEvent_AttackEnd,
	enPlayerAnimationEvent_MoveEnd,
	enPlayerAnimationEvent_None
};
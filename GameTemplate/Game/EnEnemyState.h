#pragma once

//�G�l�~�[�X�e�[�g

enum EnEnemyState
{
	enContinue,		//�X�e�[�g���p��
	enEnemyIdle,	//�ҋ@
	enEnemyWiteAndSee,	//�l�q��
	enEnemyAttackPrepare, //�U������
	enEnemyJumpSlash,	//�W�����v�؂�
	enEnemySideSlash,	//���؂�
	enEnemyReceiveDamage,	//��_���[�W
	enEnemyDie,			//���S
};

//�A�j���[�V�����C�x���g
enum EnEnemyAnimationEvent {
	enEnemyAnimationEvent_AttackStart,
	enEnemyAnimationEvent_AttackEnd,
	enEnemyAnimationEvent_None
};
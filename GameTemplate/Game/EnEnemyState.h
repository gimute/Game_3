#pragma once

//�G�l�~�[�X�e�[�g

enum EnEnemyState
{
	enEnemyIdle,	//�ҋ@
	enEnemyWiteAndSee,	//�l�q��
	enEnemyAttackPrepare, //�U������
	enEnemyJumpSlash,	//�W�����v�؂�
	enEnemySideSlash,	//���؂�
};

//�A�j���[�V�����C�x���g
enum EnEnemyAnimationEvent {
	enEnemyAnimationEvent_AttackStart,
	enEnemyAnimationEvent_AttackEnd,
	enEnemyAnimationEvent_None
};
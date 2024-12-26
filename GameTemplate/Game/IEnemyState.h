#pragma once
#include "EnEnemyState.h"

//�G�l�~�[�X�e�[�g���N���X

class Enemy;

class IEnemyState
{
public:
	//���̃X�e�[�g�ɑJ�ڂ��鎞�̏���
	virtual void Start(Enemy* enemy) {};

	//���̃X�e�[�g�ɑJ�ڂ���Ƃ��ɍs���㏈��
	virtual void End(Enemy* enemy) {};

	//�ړ�����
	virtual void Move(Vector3& position, CharacterController& charaCon) {};

	//��]����
	virtual void Rotation(Quaternion& rotation) {};

	//�A�j���[�V�����̍Đ�
	virtual void PlayAnimation(ModelRender& model) {};

	//�R���W����
	virtual void Collision(Vector3 pos, ModelRender& model) {};

	//�X�e�[�g�J��
	virtual EnEnemyState StateTransition() { return enenemyIdle; };
};


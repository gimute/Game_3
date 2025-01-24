#pragma once
#include "EnEnemyState.h"

//�G�l�~�[�X�e�[�g���N���X

class Enemy;
class Player;

class IEnemyState
{
public:
	//���̃X�e�[�g�ɑJ�ڂ��鎞�̏���
	virtual void Start(Enemy* enemy, Player* player) {};

	//���̃X�e�[�g�ɑJ�ڂ���Ƃ��ɍs���㏈��
	virtual void End(Enemy* enemy) {};

	//�ړ�����
	virtual void Move(Vector3& position, CharacterController& charaCon, Player* player) {};

	//��]����
	virtual void Rotation(Quaternion& rotation) {};

	//�A�j���[�V�����̊Ǘ�
	virtual void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) {};

	//�R���W����
	virtual void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) {};

	//�X�e�[�g�J��
	virtual EnEnemyState StateTransition() { return enEnemyIdle; };
};


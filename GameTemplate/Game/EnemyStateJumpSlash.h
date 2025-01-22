#pragma once
#include "IEnemyState.h"

//�W�����v�؂�X�e�[�g
class EnemyStateJumpSlash : public IEnemyState
{
public:
	//���̃X�e�[�g�ɑJ�ڂ��鎞�̏���
	void Start(Enemy* enemy) override;

	//���̃X�e�[�g�ɑJ�ڂ���Ƃ��ɍs���㏈��
	void End(Enemy* enemy) override;

	//�ړ�����
	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	//�A�j���[�V�����̍Đ�
	void Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent) override;

	//�R���W����
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	//�X�e�[�g�J��
	EnEnemyState StateTransition() override;

private:
	bool m_isPlayAnimation = true;	//�A�j���[�V�����Đ�����

	int m_attackBoneID;		//�U������R���W�����𐶐�����{�[����ID
	CollisionObject* m_attackCollision;	//�U���p�R���W����

	bool m_hitFlag = false;		//��_���[�W�t���O

};


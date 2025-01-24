#pragma once
#include "IEnemyState.h"

/// <summary>
/// �U�������X�e�[�g
/// </summary>
/// <remark>
/// �ǂ̍U�����s�����̌���A���̍U�����͂������܂ŋ߂Â��������s��
/// </remark>
class EnemyStateAttackPrepare : public IEnemyState
{
public:
	//�U���̎��
	enum EnAttackType
	{
		enSideSlash,	//���؂�
		enJumpSlash,	//�W�����v�؂�
		enAttackTypeNum	//�U���̎�ނ̐�
	};

	//���̃X�e�[�g�ɑJ�ڂ��鎞�̏���
	void Start(Enemy* enemy, Player* player) override;

	//�ړ�����
	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	//��]����
	void Rotation(Quaternion& rotation) override;

	//�A�j���[�V�����̍Đ�
	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	//�R���W����
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	//�X�e�[�g�J��
	EnEnemyState StateTransition() override;

private:
	float m_attackRnge;	//�U���̓͂��͈�

	EnAttackType m_attackType;

	Vector3 m_moveVec;

	bool m_attackFlag = false;	//�U�����邩

	bool hitFlag = false;		//��_���[�W�t���O

};


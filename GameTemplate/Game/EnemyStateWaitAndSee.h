#pragma once
#include "IEnemyState.h"

enum EnWalkState {
	enStop,
	enForward,
	enBack,
	enm_Clockwise,
};

//�l�q���X�e�[�g
class EnemyStateWaitAndSee : public IEnemyState
{
public:
	void Start(Enemy* enemy, Player* player) override;

	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	void Rotation(Quaternion& rotation) override;

	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	EnEnemyState StateTransition() override;

private:
	Vector3 CalcMoveVec(const Vector3 enemyPos, const Vector3 playerPos);

private:
	Vector3 enemyToPlayer = Vector3::Zero;

	float m_attackTransitionTimer = 3.0f;

	bool m_hitFlag = false;		//��_���[�W�t���O
	bool m_guradFlag = false;	//�K�[�h�t���O

	EnWalkState m_walkState = enStop;

	float m_clockwiseTimer = 1.0f;	//�v���C���[�̎��͂���鎞�Ԃ��Ǘ�����^�C�}�[
	bool m_clockwiseFlag = false;	//�v���C���[�̎��͂����t���O
};


#pragma once
#include "IPlayerState.h"


class Enemy;

//�W���X�g�����̃��b�V���U���X�e�[�g
//�܂��G�ɋ}�ڋ߂����̌�Ƀ��b�V�����J�n����

class PlayerStateJustDodgeAttack : public IPlayerState
{
public:
	enum AttackFlowState {
		enEnemyApproach,	//�G�֐ڋ�
		enAttack1,			//1�ڂ̍U��
		enAttack2,			//2�ڂ̍U��
		enAttack3,			//3�ڂ̍U��
		enEnd				//�I��
	};

	void Start(Player* player) override;
	void End(Player* player) override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void Rotation(Quaternion& rotation) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

private:
	void StateOenStep();

	CollisionObject* m_attackCollision;
	AttackFlowState m_attackFlowState = enEnemyApproach;
	int m_attackBoneID;		//�U������R���W�����𐶐�����{�[����ID

	Enemy* m_enemy;

	Vector3 playerToEnemyVec;
};


#pragma once

#include "EnEnemyState.h"
#include "EnemyStateManager.h"

//�G�l�~�[
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);


	//�A�j���[�V�����N���b�v�̃A�j���[�V�����w��p��enum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//�ҋ@�A�j���[�V����
		enAnimationClip_Walk,	//���s�A�j���[�V����
		enAnimationClip_Slash,	//�a�����[�V����
		enAnimationClip_Guard,	//�K�[�h���[�V����
		enAnimationClip_Backflip,	//�o�N�]�̃��[�V����
		enAnimationClip_DodgeLeft,	//�����
		enAnimationClip_DodgeRight,	//�E���
		enAnimationClip_Num	//�A�j���[�V�����̐�
	};

private:
	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// ���f���̏�����
	/// </summary>
	void InitModel();

private:
	ModelRender m_enemyModel;	//�G�l�~�[�̃��f��
	Vector3 m_position = Vector3::Zero;			//���f���̍��W
	Quaternion m_rotation = Quaternion::Identity;		//���f���̉�]
	CharacterController m_charaCon;	//���f���𓮂������߂̃L�����R��

	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v

	EnemyStateManager m_enemyStateManager;		
};


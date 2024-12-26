#pragma once
//�v���C���[�N���X

#include "EnPlayerState.h"
#include "PlayerStateManager.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// <summary>
	/// �v���C���[�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �v���C���[�̃��f�������_�[���擾
	/// </summary>
	/// <returns></returns>
	ModelRender* GetModel()
	{
		return &m_playerModel;
	}

	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
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
	ModelRender m_playerModel;		//�v���C���[�̃��f��
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v

	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	EnPlayerState m_playerState = enIdle;	//�v���C���[�̏��

	Vector3 m_position = Vector3::Zero;	//�v���C���[�̍��W
	Vector3 m_moveVec = Vector3::Zero;	//�v���C���[�̈ړ��x�N�g��
	Quaternion m_rotation;	//�v���C���[�̉�]

	PlayerStateManager m_playerStateManager;	//�v���C���[�X�e�[�g�}�l�[�W���[
};


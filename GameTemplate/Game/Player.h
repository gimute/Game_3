#pragma once
//�v���C���[�N���X

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void InitAnimation();

	void PlayerModelUpdate();
	void Move();
	void Rotation();
	void PlayAnimation();

	void Render(RenderContext& rc);

	//�A�j���[�V�����N���b�v�̃A�j���[�V�����w��p��enum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//�ҋ@�A�j���[�V����
		enAnimationClip_Walk,	//���s�A�j���[�V����
		enAnimationClip_Backflip,
		enAnimationClip_Num	//�A�j���[�V�����̐�
	};

	enum EnPlayerState {
		enIdle,		//�ҋ@
		enWalk,		//����
		enBackDodge		//�����
	};

private:
	ModelRender m_playerModel;		//�v���C���[�̃��f��
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v

	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	EnPlayerState m_playerState = enIdle;	//�v���C���[�̏��

	Vector3 m_position = Vector3::Zero;	//�v���C���[�̍��W
	Vector3 m_moveVec = Vector3::Zero;	//�v���C���[�̈ړ��x�N�g��
	Quaternion m_rotation;	//�v���C���[�̉�]

};


#pragma once
//�v���C���[�N���X

#include "EnPlayerState.h"
#include "PlayerStateManager.h"

class Enemy;
class PlayerHpUI;


class Player : public IGameObject
{
public:
	//�A�j���[�V�����N���b�v�̃A�j���[�V�����w��p��enum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//�ҋ@�A�j���[�V����
		enAnimationClip_Walk,	//���s�A�j���[�V����
		enAnimationClip_Slash,	//�a�����[�V����
		enAnimationClip_Guard,	//�K�[�h���[�V����
		enAnimationClip_Backflip,	//�o�N�]�̃��[�V����
		enAnimationClip_LeftDodge,	//�����
		enAnimationClip_RightDodge,	//�E���
		enAnimationClip_ReceiveDamage,		//��_���[�W
		enAnimatinoClip_DamageGuard,	//�_���[�W�K�[�h���[�V����
		enAnimationClip_LeftGuardStrafe,	//�K�[�h���ړ�
		enAnimationClip_RightGuardStrafe,	//�K�[�h�E�ړ�
		enAnimationClip_JumpSlash,		//�W�����v�؂�
		enAnimationClip_Die,			//���ڂ��A�j���[�V����
		enAnimationClip_Num	//�A�j���[�V�����̐�
	};

	

	Player();
	~Player();
	bool Start() override;
	void Update() override;

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
	void Render(RenderContext& rc) override;

	/// <summary>
	/// �ߑ����Ă���G�l�~�[���擾
	/// </summary>
	Enemy*& GetTargetEnemy()
	{
		return mlockOnEnemy;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(Quaternion rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// �_���[�W����
	/// </summary>
	void Damage(float damageAmount);

	/// <summary>
	/// ���݂�HP���擾
	/// </summary>
	/// <returns></returns>
	float GetNowHp();

	//�X�e�[�^�X�Ȃǂ̏�����
	void InitStatus();

	//�A�j���[�V�����C�x���g�p�֐�
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	const bool IsEnemyLockOn() const
	{
		return m_isEnemyLockOn;
	}

	void PlayerLose()
	{
		m_loseFlag = true;
	}

	const bool GetLoseFlag() const
	{
		return m_loseFlag;
	}

	/*void SetEnemyLockOnFlag(bool flag)
	{
		m_isEnemyLockOn = flag;
	}*/

private:
	ModelRender m_playerModel;		//�v���C���[�̃��f��
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v

	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	EnPlayerState m_playerState = enPlayerIdle;	//�v���C���[�̏��

	Vector3 m_position = Vector3::Zero;	//�v���C���[�̍��W
	Vector3 m_moveVec = Vector3::Zero;	//�v���C���[�̈ړ��x�N�g��
	Quaternion m_rotation;	//�v���C���[�̉�]

	PlayerStateManager m_playerStateManager;	//�v���C���[�X�e�[�g�}�l�[�W���[

	Enemy* mlockOnEnemy = nullptr;	//�ߑ��G�l�~�[
	PlayerHpUI* m_hpUI = nullptr;

	EnPlayerAnimationEvent m_enAnimationEvent = enPlayerAnimationEvent_None;

	bool m_isEnemyLockOn = false;	//���b�N�I���t���O

	bool m_loseFlag = false;	//�s�k�t���O
};


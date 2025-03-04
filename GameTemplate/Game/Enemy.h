#pragma once

#include "EnEnemyState.h"
#include "EnemyStateManager.h"

class EnemyHpUI;

//�G�l�~�[
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;


	//�A�j���[�V�����N���b�v�̃A�j���[�V�����w��p��enum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//�ҋ@�A�j���[�V����
		enAnimationClip_Walk,	//���s�A�j���[�V����
		enAnimationClip_BackWalk,	//���������[�V����
		enAnimationClip_Slash,	//�a�����[�V����
		enAnimationClip_JumpSlash,	//�W�����v�؂�
		enAnimationClip_Guard,	//�K�[�h���[�V����
		enAnimatinoClip_DamageGuard,	//�_���[�W�K�[�h���[�V����
		enAnimationClip_Backflip,	//�o�N�]�̃��[�V����
		enAnimationClip_DodgeLeft,	//�����
		enAnimationClip_RightDodge,	//�E���
		enAnimationClip_LateralMovement_Left,	//���ړ��A�j���[�V����
		enAnimationClip_LateralMovement_Right,	//�E�ړ��A�j���[�V����
		enAnimationClip_ReceiveDamage,	//��_���[�W���[�V����
		enAnimationClip_Die,			//���ڂ��A�j���[�V����
		enAnimationClip_Num	//�A�j���[�V�����̐�
	};

	/// <summary>
	/// �G�l�~�[�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �G�l�~�[�̃��f�������_�[���擾
	/// </summary>
	/// <returns></returns>
	ModelRender* GetModel()
	{
		return &m_enemyModel;
	}

	/// <summary>
	/// �A�j���[�V�����C�x���g�p�֐�
	/// </summary>
	/// <param name="clipName"></param>
	/// <param name="eventName"></param>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	//��������
	void Delete();

	/// <summary>
	/// �_���[�W����
	/// </summary>
	void Damage(float damageAmount);

	/// <summary>
	/// ���݂�HP���擾
	/// </summary>
	/// <returns></returns>
	float GetNowHP();

	void HPUIInit();

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

	EnEnemyAnimationEvent m_enAnimationEvent = enEnemyAnimationEvent_None;

	EnemyHpUI* m_enemyHpUI = nullptr;
};


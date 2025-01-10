#include "stdafx.h"
#include "Player.h"
//�v���C���[

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	//�X�e�[�g�}�l�[�W���[������
	m_playerStateManager.Init(this);

	//�A�j���[�V�����̏�����
	InitAnimation();

	//�v���C���[���f���̏�����
	m_playerModel.Init("Assets/modelData/paladin/paladin_2.tkm", m_animationClips, enAnimationClip_Num);
	m_playerModel.SetScale(Vector3::One * 2.0f);
	m_playerModel.Update(); 

	//�L�����N�^�[�R���g���[���[�̏�����
	m_charaCon.Init(30.0f, 80.0f, m_position);

	//m_playerModel.Init("Assets/modelData/TestModels/bot.tkm", m_animationClips, enAnimationClip_Num);
	//m_playerModel.SetScale(Vector3::One * 2.0f);
	//m_playerModel.Update();
	
	return true;
}

void Player::InitAnimation()
{
	//�A�j���[�V�����̃��[�h�A���[�v�t���O�̐ݒ�
	//�ҋ@�A�j���[�V����
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/paladin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//���s�A�j���[�V����
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/paladin/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//�a���A�j���[�V����
	m_animationClips[enAnimationClip_Slash].Load("Assets/animData/paladin/sideSlash.tka");
	m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	//�K�[�h�A�j���[�V����
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/paladin/guardIdle.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//�o�N�]�A�j���[�V����
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/paladin/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	//������A�j���[�V����
	m_animationClips[enAnimationClip_LeftDodge].Load("Assets/animData/paladin/leftDodge.tka");
	m_animationClips[enAnimationClip_LeftDodge].SetLoopFlag(false);
	//�E����A�j���[�V����
	m_animationClips[enAnimationClip_RightDodge].Load("Assets/animData/paladin/rightDodge.tka");
	m_animationClips[enAnimationClip_RightDodge].SetLoopFlag(false);
	//��_���[�W�A�j���[�V����
	m_animationClips[enAnimationClip_Damege].Load("Assets/animData/paladin/damage.tka");
	m_animationClips[enAnimationClip_Damege].SetLoopFlag(false);
	//�_���[�W�K�[�h���[�V����
	m_animationClips[enAnimatinoClip_DamageGuard].Load("Assets/animData/paladin/damageGuard.tka");
	m_animationClips[enAnimatinoClip_DamageGuard].SetLoopFlag(false);
	//�K�[�h���ړ����[�V����
	m_animationClips[enAnimationClip_LeftGuardStrafe].Load("Assets/animData/paladin/leftGuardStrafe.tka");
	m_animationClips[enAnimationClip_LeftGuardStrafe].SetLoopFlag(false);
	//�K�[�h�E�ړ����[�V����
	m_animationClips[enAnimationClip_RightGuardStrafe].Load("Assets/animData/paladin/rightGuardStrafe.tka");
	m_animationClips[enAnimationClip_RightGuardStrafe].SetLoopFlag(false);



	////�A�j���[�V�����̃��[�h�A���[�v�t���O�̐ݒ�
	////�ҋ@�A�j���[�V����
	//m_animationClips[enAnimationClip_Idle].Load("Assets/animData/test_player/idle.tka");
	//m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	////���s�A�j���[�V����
	//m_animationClips[enAnimationClip_Walk].Load("Assets/animData/test_player/walk.tka");
	//m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	////�a���A�j���[�V����
	//m_animationClips[enAnimationClip_Slash].Load("Assets/animData/test_player/slash.tka");
	//m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	////�K�[�h�A�j���[�V����
	//m_animationClips[enAnimationClip_Guard].Load("Assets/animData/test_player/guard.tka");
	//m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	////�o�N�]�A�j���[�V����
	//m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/test_player/backflip.tka");
	//m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	////������A�j���[�V����
	//m_animationClips[enAnimationClip_DodgeLeft].Load("Assets/animData/test_player/DodgeLeft.tka");
	//m_animationClips[enAnimationClip_DodgeLeft].SetLoopFlag(false);
	////�E����A�j���[�V����
	//m_animationClips[enAnimationClip_DodgeRight].Load("Assets/animData/test_player/DodgeRight.tka");
	//m_animationClips[enAnimationClip_DodgeRight].SetLoopFlag(false);

}

void Player::Update()
{
	m_playerStateManager.Move(m_position, m_charaCon);

	m_playerStateManager.Rotation(m_rotation);

	m_playerStateManager.PlayAnimation(m_playerModel);

	m_playerModel.SetPosition(m_position);
	m_playerModel.SetRotation(m_rotation);
	m_playerModel.Update();
	m_charaCon.SetPosition(m_position);;

	m_playerStateManager.Collision(m_position, m_playerModel, m_charaCon);

	//�X�e�[�g�J�ڏ���
	//�ǂ̃X�e�[�g�ɑJ�ڂ��邩�󂯎��
	EnPlayerState m_state = m_playerStateManager.StateTransition();
	//�󂯎�����X�e�[�g�ɃZ�b�g
	m_playerStateManager.SetState(m_state);

}


void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);
}

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
	InitAnimation();

	//�v���C���[���f���̏�����
	m_playerModel.Init("Assets/modelData/TestModels/bot.tkm", m_animationClips, enAnimationClip_Num);
	m_playerModel.SetScale(Vector3::One * 2.0f);
	m_playerModel.Update();

	//�L�����N�^�[�R���g���[���[�̏�����
	m_charaCon.Init(30.0f, 80.0f, m_position);

	return true;
}

void Player::InitAnimation()
{
	//�A�j���[�V�����̃��[�h�A���[�v�t���O�̐ݒ�
	//�ҋ@�A�j���[�V����
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/test_player/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//���s�A�j���[�V����
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/test_player/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//
}

void Player::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_playerState = enBackDodge;
	}

	//�v���C���[���f���̍X�V
	PlayerModelUpdate();
}

void Player::PlayerModelUpdate()
{
	//�v���C���[�̈ړ�
	Move();
	//�v���C���[�̉�]
	Rotation();
	//�v���C���[�̃A�j���[�V����
	PlayAnimation();

	//�v���C���[���f�����X�V
	m_playerModel.Update();
}

void Player::Move()
{
	m_moveVec = Vector3::Zero;	//�ړ��x�N�g��

	//���X�e�B�b�N�̓��͂��擾
	Vector3 stickL = Vector3::Zero;
	stickL.x = g_pad[0]->GetLStickXF() * 150;
	stickL.y = g_pad[0]->GetLStickYF() * 150;

	//�X�e�B�b�N�̓��͂��ړ��x�N�g���ɕϊ�
	m_moveVec.x += stickL.x;
	m_moveVec.z += stickL.y;

	//�L�����R�����g���č��W���X�V
	m_position = m_charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());

	//�v���C���[���f���ƃL�����R���̍��W���Z�b�g
	m_playerModel.SetPosition(m_position);
	m_charaCon.SetPosition(m_position);
}

void Player::Rotation()
{
	//�i�s�����Ƀv���C���[����������
	 
	//���������ړ����ĂȂ������珈�����΂�
	if (fabsf(m_moveVec.x) < 0.001f && fabsf(m_moveVec.z) < 0.001f) {
		return;
	}

	//�ړ��x�N�g�������]�����߂�
	m_rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));

	//�v���C���[���f���̉�]��ݒ肷��B
	m_playerModel.SetRotation(m_rotation);
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case enIdle:
		m_playerModel.PlayAnimation(enAnimationClip_Idle, 0.1f);
		break;

	case enWalk:
		m_playerModel.PlayAnimation(enAnimationClip_Walk, 0.1f);
		break;

	default:
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);

}

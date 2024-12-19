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
	m_playerStateManager.Init(this);

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
	//�a���A�j���[�V����
	m_animationClips[enAnimationClip_Slash].Load("Assets/animData/test_player/slash.tka");
	m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	//�K�[�h�A�j���[�V����
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/test_player/guard.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//�o�N�]�A�j���[�V����
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/test_player/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);

}

void Player::Update()
{
	m_playerStateManager.Move(m_position, m_charaCon);

	m_playerStateManager.Rotation(m_rotation);

	m_playerStateManager.AnimationPlay(m_playerModel);

	m_playerModel.SetPosition(m_position);
	m_playerModel.SetRotation(m_rotation);
	m_playerModel.Update();
	m_charaCon.SetPosition(m_position);;

	m_playerStateManager.Collision(m_position, m_playerModel);

	m_playerStateManager.SetState(m_playerStateManager.StateTransition());

	/*if (fabsf(g_pad[0]->GetLStickXF()) > 0.001f || fabsf(g_pad[0]->GetLStickYF()) > 0.001f)
	{
		m_state = &m_stateWalk;
	}
	else
	{
		m_state = &m_stateIdle;
	}*/
}


void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);

}

#include "stdafx.h"
#include "Enemy.h"

//�G�l�~�[

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	//�A�j���[�V�����̏�����
	InitAnimation();

	//���f���̏�����
	InitModel();

	m_charaCon.Init(30.0f, 80.0f, m_position);

	//�X�e�[�g�}�l�[�W���[������
	m_enemyStateManager.Init(this);

	return true;
}



void Enemy::Update()
{
	m_enemyStateManager.Move(m_position, m_charaCon);

	m_enemyStateManager.Rotation(m_rotation);

	m_enemyStateManager.Animation(m_enemyModel, enEnemyAnimationEvent_None);

	m_enemyModel.SetPosition(m_position);
	m_enemyModel.SetRotation(m_rotation);
	m_enemyModel.Update();

	m_charaCon.SetPosition(m_position);


	m_enemyStateManager.Collision(m_position, m_enemyModel);

	m_enemyStateManager.StateTransition();
}

void Enemy::Render(RenderContext& rc)
{
	m_enemyModel.Draw(rc);
}

void Enemy::InitAnimation()
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
	//�W�����v�؂�A�j���[�V����
	m_animationClips[enAnimationClip_JumpSlash].Load("Assets/animData/test_player/jumpSlash.tka");
	m_animationClips[enAnimationClip_JumpSlash].SetLoopFlag(false);
	//�K�[�h�A�j���[�V����
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/test_player/guard.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//�o�N�]�A�j���[�V����
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/test_player/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	//������A�j���[�V����
	m_animationClips[enAnimationClip_DodgeLeft].Load("Assets/animData/test_player/DodgeLeft.tka");
	m_animationClips[enAnimationClip_DodgeLeft].SetLoopFlag(false);
	//�E����A�j���[�V����
	m_animationClips[enAnimationClip_RightDodge].Load("Assets/animData/test_player/DodgeRight.tka");
	m_animationClips[enAnimationClip_RightDodge].SetLoopFlag(false);
	//���ړ��A�j���[�V����
	m_animationClips[enAnimationClip_LateralMovement_Left].Load("Assets/animData/test_player/LateralMovement_Left.tka");
	m_animationClips[enAnimationClip_LateralMovement_Left].SetLoopFlag(true);
	//�E�ړ��A�j���[�V����
	m_animationClips[enAnimationClip_LateralMovement_Right].Load("Assets/animData/test_player/LateralMovement_Right.tka");
	m_animationClips[enAnimationClip_LateralMovement_Right].SetLoopFlag(true);

}

void Enemy::InitModel()
{
	m_enemyModel.Init("Assets/modelData/TestModels/bot.tkm", m_animationClips, enAnimationClip_Num);
	m_enemyModel.SetScale(Vector3::One * 2.0f);
	m_enemyModel.Update();
}


#include "stdafx.h"
#include "Enemy.h"

#include "EnemyHpUI.h"

//�G�l�~�[

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	DeleteGO(m_enemyHpUI);
}

void Enemy::Delete()
{
	DeleteGO(this);
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

	m_enemyHpUI = NewGO<EnemyHpUI>(0, "enemyHpUI");
	HPUIInit();

	return true;
}



void Enemy::Update()
{
	m_enemyStateManager.Move(m_position, m_charaCon);

	m_enemyStateManager.Rotation(m_rotation);

	m_enemyStateManager.Animation(m_enemyModel, m_enAnimationEvent);

	m_enemyModel.SetPosition(m_position);
	m_enemyModel.SetRotation(m_rotation);
	m_enemyModel.Update();

	m_charaCon.SetPosition(m_position);


	m_enemyStateManager.Collision(m_position, m_enemyModel, m_charaCon);

	m_enemyStateManager.StateTransition();
}

void Enemy::InitAnimation()
{
	//�ҋ@�A�j���[�V����
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/paladin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//���s�A�j���[�V����
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/paladin/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//���s�A�j���[�V����
	m_animationClips[enAnimationClip_BackWalk].Load("Assets/animData/paladin/backWalk.tka");
	m_animationClips[enAnimationClip_BackWalk].SetLoopFlag(true);
	//�a���A�j���[�V����
	m_animationClips[enAnimationClip_Slash].Load("Assets/animData/paladin/Enemy/sideSlash.tka");
	m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	//�W�����v�؂�A�j���[�V����
	m_animationClips[enAnimationClip_JumpSlash].Load("Assets/animData/paladin/Enemy/jumpSlash.tka");
	m_animationClips[enAnimationClip_JumpSlash].SetLoopFlag(false);
	//�K�[�h�A�j���[�V����
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/paladin/guardIdle.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//�o�N�]�A�j���[�V����
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/paladin/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	//������A�j���[�V����
	m_animationClips[enAnimationClip_DodgeLeft].Load("Assets/animData/paladin/leftDodge.tka");
	m_animationClips[enAnimationClip_DodgeLeft].SetLoopFlag(false);
	//�E����A�j���[�V����
	m_animationClips[enAnimationClip_RightDodge].Load("Assets/animData/paladin/rightDodge.tka");
	m_animationClips[enAnimationClip_RightDodge].SetLoopFlag(false);
	//���ړ��A�j���[�V����
	m_animationClips[enAnimationClip_LateralMovement_Left].Load("Assets/animData/paladin/leftGuardStrafe.tka");
	m_animationClips[enAnimationClip_LateralMovement_Left].SetLoopFlag(true);
	//�E�ړ��A�j���[�V����
	m_animationClips[enAnimationClip_LateralMovement_Right].Load("Assets/animData/paladin/rightGuardStrafe.tka");
	m_animationClips[enAnimationClip_LateralMovement_Right].SetLoopFlag(true);
	//��_���[�W�A�j���[�V����
	m_animationClips[enAnimationClip_ReceiveDamage].Load("Assets/animData/paladin/receiveDamage.tka");
	m_animationClips[enAnimationClip_ReceiveDamage].SetLoopFlag(false);
	//���ڂ��A�j���[�V����
	m_animationClips[enAnimationClip_Die].Load("Assets/animData/paladin/die.tka");
	m_animationClips[enAnimationClip_Die].SetLoopFlag(false);
}

void Enemy::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"attackEnd") == 0)
	{
		m_enAnimationEvent = enEnemyAnimationEvent_AttackEnd;
	}

	if (wcscmp(eventName, L"attackStart") == 0)
	{
		m_enAnimationEvent = enEnemyAnimationEvent_AttackStart;
	}
}

void Enemy::InitModel()
{
	m_enemyModel.Init("Assets/modelData/paladin/paladin.tkm", m_animationClips, enAnimationClip_Num);
	m_enemyModel.SetScale(Vector3::One * 2.0f);
	m_enemyModel.Update();

	//�A�j���[�V�����C�x���g
	m_enemyModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});
}

void Enemy::Damage(float damageAmount)
{
	m_enemyHpUI->Damage(damageAmount);
}

float Enemy::GetNowHP()
{
	return m_enemyHpUI->GetNowHp();
}

void Enemy::HPUIInit()
{
	m_enemyHpUI->Init(this, 10.0f);
}

void Enemy::Render(RenderContext& rc)
{
	m_enemyModel.Draw(rc);
}

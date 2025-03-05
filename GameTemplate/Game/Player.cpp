#include "stdafx.h"
#include "Player.h"

#include "PlayerHpUI.h"
#include "PlayerParameter.h"
#include "Enemy.h"

Player::Player()
{

}

Player::~Player()
{
	DeleteGO(m_hpUI);
}

bool Player::Start()
{
	//�X�e�[�g�}�l�[�W���[������
	m_playerStateManager.Init(this);

	//�A�j���[�V�����̏�����
	InitAnimation();

	//�v���C���[���f���̏�����
	m_playerModel.Init("Assets/modelData/paladin/paladin.tkm", m_animationClips, enAnimationClip_Num);
	m_playerModel.SetScale(Vector3::One * 2.0f);
	m_playerModel.Update(); 

	//�L�����N�^�[�R���g���[���[�̏�����
	m_charaCon.Init(30.0f, 80.0f, m_position);

	//�{���Ȃ����̓G��ߑ����鏈�������邪�Ƃ肠�����͂����
	m_lockOnEnemy = FindGO<Enemy>("enemy");
	
	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
	m_playerModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_hpUI = NewGO<PlayerHpUI>(0,"playerHpUI");
	InitStatus();

	return true;
}

void Player::InitAnimation()
{
	//�A�j���[�V�����̃��[�h�A���[�v�t���O�̐ݒ�
	//�ҋ@�A�j���[�V����
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/paladin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//�����A�j���[�V����
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/paladin/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//�_�b�V���A�j���[�V����
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/paladin/Run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//�a���A�j���[�V����
	m_animationClips[enAnimationClip_Slash].Load("Assets/animData/paladin/player/sideSlash.tka");
	m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	//�K�[�h�A�j���[�V����
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/paladin/guardIdle.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//�o�N�]�A�j���[�V����
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/paladin/Player/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	//������A�j���[�V����
	m_animationClips[enAnimationClip_LeftDodge].Load("Assets/animData/paladin/Player/leftDodge.tka");
	m_animationClips[enAnimationClip_LeftDodge].SetLoopFlag(false);
	//�E����A�j���[�V����
	m_animationClips[enAnimationClip_RightDodge].Load("Assets/animData/paladin/Player/rightDodge.tka");
	m_animationClips[enAnimationClip_RightDodge].SetLoopFlag(false);
	//��_���[�W�A�j���[�V����
	m_animationClips[enAnimationClip_ReceiveDamage].Load("Assets/animData/paladin/receiveDamage.tka");
	m_animationClips[enAnimationClip_ReceiveDamage].SetLoopFlag(false);
	//�_���[�W�K�[�h���[�V����
	m_animationClips[enAnimatinoClip_DamageGuard].Load("Assets/animData/paladin/damageGuard.tka");
	m_animationClips[enAnimatinoClip_DamageGuard].SetLoopFlag(false);
	//�K�[�h���ړ����[�V����
	m_animationClips[enAnimationClip_LeftGuardStrafe].Load("Assets/animData/paladin/leftGuardStrafe.tka");
	m_animationClips[enAnimationClip_LeftGuardStrafe].SetLoopFlag(false);
	//�K�[�h�E�ړ����[�V����
	m_animationClips[enAnimationClip_RightGuardStrafe].Load("Assets/animData/paladin/rightGuardStrafe.tka");
	m_animationClips[enAnimationClip_RightGuardStrafe].SetLoopFlag(false);
	//�W�����v�؂�
	m_animationClips[enAnimationClip_JumpSlash].Load("Assets/animData/paladin/player/jumpSlash.tka");
	m_animationClips[enAnimationClip_JumpSlash].SetLoopFlag(false);
	//���ڂ��A�j���[�V����
	m_animationClips[enAnimationClip_Die].Load("Assets/animData/paladin/die.tka");
	m_animationClips[enAnimationClip_Die].SetLoopFlag(false);
}

void Player::Update()
{
	if (g_pad[0]->IsTrigger(PLAYER_GUARD_BUTTON))
	{
		//���b�N�I���G�l�~�[���X�V
		LockOnEnemyUpdate();
	}

	//�K�[�h�{�^����������Ă���Ԃ̓��b�N�I���t���O���I���ɂ���
	if (g_pad[0]->IsPress(PLAYER_GUARD_BUTTON) && m_lockOnEnemy != nullptr)
	{
		m_isEnemyLockOn = true;

		//�G�����񂾂�
		if (m_lockOnEnemy->IsDead())
		{
			m_lockOnEnemy = nullptr;
			m_isEnemyLockOn = false;
		}
	}
	else
	{
		m_isEnemyLockOn = false;
	}


	m_playerStateManager.Move(m_position, m_charaCon);
	m_playerStateManager.Rotation(m_rotation, m_position);
	m_playerStateManager.Animation(m_playerModel, m_enAnimationEvent);

	//���f���̍X�V
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


void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"attackEnd") == 0)
	{
		m_enAnimationEvent = enPlayerAnimationEvent_AttackEnd;
	}

	if (wcscmp(eventName, L"attackStart") == 0)
	{
		m_enAnimationEvent = enPlayerAnimationEvent_AttackStart;
	}

	if (wcscmp(eventName, L"moveEnd") == 0)
	{
		m_enAnimationEvent = enPlayerAnimationEvent_MoveEnd;
	}
}

void Player::LockOnEnemyUpdate()
{
	//��ԋ߂��G��T��

	float minLengeSq = 1000.0f * 1000.0f;	//��ԋ߂��G�l�~�[�Ƃ̋�����2��
	Vector3 EnemyToPlayer;	//�G�l�~�[����v���C���[�܂Ńx�N�g��
	float EnemyToPlayerLengeSq;	//�G�l�~�[����v���C���[�܂Ńx�N�g���̒�����2��

	for (const Enemy* const &enemy : *m_enemyList)
	{
		//�g�������v�Z�ŋ��߂�
		EnemyToPlayer = m_position - enemy->GetPosition();
		EnemyToPlayerLengeSq = EnemyToPlayer.LengthSq();

		//���߂��Ȃ烍�b�N�I���G�l�~�[���X�V
		if (EnemyToPlayerLengeSq < minLengeSq)
		{
			minLengeSq = EnemyToPlayerLengeSq;
			m_lockOnEnemy = enemy;
		}
	}
}

void Player::Damage(float damageAmount)
{
	m_hpUI->Damage(damageAmount);
}

float Player::GetNowHp()
{
	return m_hpUI->GetNowHp();
}

void Player::InitStatus()
{
	m_hpUI->Init(8.0f);
}

void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);
}

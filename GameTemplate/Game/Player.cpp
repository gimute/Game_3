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
	//ステートマネージャー初期化
	m_playerStateManager.Init(this);

	//アニメーションの初期化
	InitAnimation();

	//プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/paladin/paladin.tkm", m_animationClips, enAnimationClip_Num);
	m_playerModel.SetScale(Vector3::One * 2.0f);
	m_playerModel.Update(); 

	//キャラクターコントローラーの初期化
	m_charaCon.Init(30.0f, 80.0f, m_position);

	//本来なら特定の敵を捕捉する処理がいるがとりあえずはこれで
	m_lockOnEnemy = FindGO<Enemy>("enemy");
	
	//アニメーションイベント用の関数を設定する。
	m_playerModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_hpUI = NewGO<PlayerHpUI>(0,"playerHpUI");
	InitStatus();

	return true;
}

void Player::InitAnimation()
{
	//アニメーションのロード、ループフラグの設定
	//待機アニメーション
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/paladin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//歩きアニメーション
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/paladin/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//ダッシュアニメーション
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/paladin/Run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//斬撃アニメーション
	m_animationClips[enAnimationClip_Slash].Load("Assets/animData/paladin/player/sideSlash.tka");
	m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	//ガードアニメーション
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/paladin/guardIdle.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//バク転アニメーション
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/paladin/Player/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	//左回避アニメーション
	m_animationClips[enAnimationClip_LeftDodge].Load("Assets/animData/paladin/Player/leftDodge.tka");
	m_animationClips[enAnimationClip_LeftDodge].SetLoopFlag(false);
	//右回避アニメーション
	m_animationClips[enAnimationClip_RightDodge].Load("Assets/animData/paladin/Player/rightDodge.tka");
	m_animationClips[enAnimationClip_RightDodge].SetLoopFlag(false);
	//被ダメージアニメーション
	m_animationClips[enAnimationClip_ReceiveDamage].Load("Assets/animData/paladin/receiveDamage.tka");
	m_animationClips[enAnimationClip_ReceiveDamage].SetLoopFlag(false);
	//ダメージガードモーション
	m_animationClips[enAnimatinoClip_DamageGuard].Load("Assets/animData/paladin/damageGuard.tka");
	m_animationClips[enAnimatinoClip_DamageGuard].SetLoopFlag(false);
	//ガード左移動モーション
	m_animationClips[enAnimationClip_LeftGuardStrafe].Load("Assets/animData/paladin/leftGuardStrafe.tka");
	m_animationClips[enAnimationClip_LeftGuardStrafe].SetLoopFlag(false);
	//ガード右移動モーション
	m_animationClips[enAnimationClip_RightGuardStrafe].Load("Assets/animData/paladin/rightGuardStrafe.tka");
	m_animationClips[enAnimationClip_RightGuardStrafe].SetLoopFlag(false);
	//ジャンプ切り
	m_animationClips[enAnimationClip_JumpSlash].Load("Assets/animData/paladin/player/jumpSlash.tka");
	m_animationClips[enAnimationClip_JumpSlash].SetLoopFlag(false);
	//しぼうアニメーション
	m_animationClips[enAnimationClip_Die].Load("Assets/animData/paladin/die.tka");
	m_animationClips[enAnimationClip_Die].SetLoopFlag(false);
}

void Player::Update()
{
	if (g_pad[0]->IsTrigger(PLAYER_GUARD_BUTTON))
	{
		//ロックオンエネミーを更新
		LockOnEnemyUpdate();
	}

	//ガードボタンが押されている間はロックオンフラグをオンにする
	if (g_pad[0]->IsPress(PLAYER_GUARD_BUTTON) && m_lockOnEnemy != nullptr)
	{
		m_isEnemyLockOn = true;

		//敵が死んだら
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

	//モデルの更新
	m_playerModel.SetPosition(m_position);
	m_playerModel.SetRotation(m_rotation);
	m_playerModel.Update();

	m_charaCon.SetPosition(m_position);;

	m_playerStateManager.Collision(m_position, m_playerModel, m_charaCon);

	//ステート遷移処理
	//どのステートに遷移するか受け取る
	EnPlayerState m_state = m_playerStateManager.StateTransition();
	//受け取ったステートにセット
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
	//一番近い敵を探す

	float minLengeSq = 1000.0f * 1000.0f;	//一番近いエネミーとの距離の2乗
	Vector3 EnemyToPlayer;	//エネミーからプレイヤーまでベクトル
	float EnemyToPlayerLengeSq;	//エネミーからプレイヤーまでベクトルの長さの2乗

	for (const Enemy* const &enemy : *m_enemyList)
	{
		//使う情報を計算で求める
		EnemyToPlayer = m_position - enemy->GetPosition();
		EnemyToPlayerLengeSq = EnemyToPlayer.LengthSq();

		//より近いならロックオンエネミーを更新
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

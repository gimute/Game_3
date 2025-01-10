#include "stdafx.h"
#include "Player.h"
//プレイヤー

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	//ステートマネージャー初期化
	m_playerStateManager.Init(this);

	//アニメーションの初期化
	InitAnimation();

	//プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/paladin/paladin_2.tkm", m_animationClips, enAnimationClip_Num);
	m_playerModel.SetScale(Vector3::One * 2.0f);
	m_playerModel.Update(); 

	//キャラクターコントローラーの初期化
	m_charaCon.Init(30.0f, 80.0f, m_position);

	//m_playerModel.Init("Assets/modelData/TestModels/bot.tkm", m_animationClips, enAnimationClip_Num);
	//m_playerModel.SetScale(Vector3::One * 2.0f);
	//m_playerModel.Update();
	
	return true;
}

void Player::InitAnimation()
{
	//アニメーションのロード、ループフラグの設定
	//待機アニメーション
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/paladin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//歩行アニメーション
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/paladin/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//斬撃アニメーション
	m_animationClips[enAnimationClip_Slash].Load("Assets/animData/paladin/sideSlash.tka");
	m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	//ガードアニメーション
	m_animationClips[enAnimationClip_Guard].Load("Assets/animData/paladin/guardIdle.tka");
	m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	//バク転アニメーション
	m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/paladin/backflip.tka");
	m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	//左回避アニメーション
	m_animationClips[enAnimationClip_LeftDodge].Load("Assets/animData/paladin/leftDodge.tka");
	m_animationClips[enAnimationClip_LeftDodge].SetLoopFlag(false);
	//右回避アニメーション
	m_animationClips[enAnimationClip_RightDodge].Load("Assets/animData/paladin/rightDodge.tka");
	m_animationClips[enAnimationClip_RightDodge].SetLoopFlag(false);
	//被ダメージアニメーション
	m_animationClips[enAnimationClip_Damege].Load("Assets/animData/paladin/damage.tka");
	m_animationClips[enAnimationClip_Damege].SetLoopFlag(false);
	//ダメージガードモーション
	m_animationClips[enAnimatinoClip_DamageGuard].Load("Assets/animData/paladin/damageGuard.tka");
	m_animationClips[enAnimatinoClip_DamageGuard].SetLoopFlag(false);
	//ガード左移動モーション
	m_animationClips[enAnimationClip_LeftGuardStrafe].Load("Assets/animData/paladin/leftGuardStrafe.tka");
	m_animationClips[enAnimationClip_LeftGuardStrafe].SetLoopFlag(false);
	//ガード右移動モーション
	m_animationClips[enAnimationClip_RightGuardStrafe].Load("Assets/animData/paladin/rightGuardStrafe.tka");
	m_animationClips[enAnimationClip_RightGuardStrafe].SetLoopFlag(false);



	////アニメーションのロード、ループフラグの設定
	////待機アニメーション
	//m_animationClips[enAnimationClip_Idle].Load("Assets/animData/test_player/idle.tka");
	//m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	////歩行アニメーション
	//m_animationClips[enAnimationClip_Walk].Load("Assets/animData/test_player/walk.tka");
	//m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	////斬撃アニメーション
	//m_animationClips[enAnimationClip_Slash].Load("Assets/animData/test_player/slash.tka");
	//m_animationClips[enAnimationClip_Slash].SetLoopFlag(false);
	////ガードアニメーション
	//m_animationClips[enAnimationClip_Guard].Load("Assets/animData/test_player/guard.tka");
	//m_animationClips[enAnimationClip_Guard].SetLoopFlag(true);
	////バク転アニメーション
	//m_animationClips[enAnimationClip_Backflip].Load("Assets/animData/test_player/backflip.tka");
	//m_animationClips[enAnimationClip_Backflip].SetLoopFlag(false);
	////左回避アニメーション
	//m_animationClips[enAnimationClip_DodgeLeft].Load("Assets/animData/test_player/DodgeLeft.tka");
	//m_animationClips[enAnimationClip_DodgeLeft].SetLoopFlag(false);
	////右回避アニメーション
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

	//ステート遷移処理
	//どのステートに遷移するか受け取る
	EnPlayerState m_state = m_playerStateManager.StateTransition();
	//受け取ったステートにセット
	m_playerStateManager.SetState(m_state);

}


void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);
}

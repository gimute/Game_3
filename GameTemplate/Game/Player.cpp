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
	InitAnimation();

	//プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/TestModels/bot.tkm", m_animationClips, enAnimationClip_Num);
	m_playerModel.SetScale(Vector3::One * 2.0f);
	m_playerModel.Update();

	//キャラクターコントローラーの初期化
	m_charaCon.Init(30.0f, 80.0f, m_position);

	return true;
}

void Player::InitAnimation()
{
	//アニメーションのロード、ループフラグの設定
	//待機アニメーション
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/test_player/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//歩行アニメーション
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

	//プレイヤーモデルの更新
	PlayerModelUpdate();
}

void Player::PlayerModelUpdate()
{
	//プレイヤーの移動
	Move();
	//プレイヤーの回転
	Rotation();
	//プレイヤーのアニメーション
	PlayAnimation();

	//プレイヤーモデルを更新
	m_playerModel.Update();
}

void Player::Move()
{
	m_moveVec = Vector3::Zero;	//移動ベクトル

	//左スティックの入力を取得
	Vector3 stickL = Vector3::Zero;
	stickL.x = g_pad[0]->GetLStickXF() * 150;
	stickL.y = g_pad[0]->GetLStickYF() * 150;

	//スティックの入力を移動ベクトルに変換
	m_moveVec.x += stickL.x;
	m_moveVec.z += stickL.y;

	//キャラコンを使って座標を更新
	m_position = m_charaCon.Execute(m_moveVec, g_gameTime->GetFrameDeltaTime());

	//プレイヤーモデルとキャラコンの座標をセット
	m_playerModel.SetPosition(m_position);
	m_charaCon.SetPosition(m_position);
}

void Player::Rotation()
{
	//進行方向にプレイヤーを向かせる
	 
	//そもそも移動してなかったら処理を飛ばす
	if (fabsf(m_moveVec.x) < 0.001f && fabsf(m_moveVec.z) < 0.001f) {
		return;
	}

	//移動ベクトルから回転を求める
	m_rotation.SetRotationY(atan2(m_moveVec.x, m_moveVec.z));

	//プレイヤーモデルの回転を設定する。
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

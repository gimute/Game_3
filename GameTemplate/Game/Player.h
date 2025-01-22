#pragma once
//プレイヤークラス

#include "EnPlayerState.h"
#include "PlayerStateManager.h"

class Enemy;
class PlayerHpUI;


class Player : public IGameObject
{
public:
	//アニメーションクリップのアニメーション指定用のenum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//待機アニメーション
		enAnimationClip_Walk,	//歩行アニメーション
		enAnimationClip_Slash,	//斬撃モーション
		enAnimationClip_Guard,	//ガードモーション
		enAnimationClip_Backflip,	//バク転のモーション
		enAnimationClip_LeftDodge,	//左回避
		enAnimationClip_RightDodge,	//右回避
		enAnimationClip_ReceiveDamage,		//被ダメージ
		enAnimatinoClip_DamageGuard,	//ダメージガードモーション
		enAnimationClip_LeftGuardStrafe,	//ガード左移動
		enAnimationClip_RightGuardStrafe,	//ガード右移動
		enAnimationClip_JumpSlash,	
		enAnimationClip_Num	//アニメーションの数
	};

	

	Player();
	~Player();
	bool Start() override;
	void Update() override;

	/// <summary>
	/// プレイヤーのポジションを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// プレイヤーのモデルレンダーを取得
	/// </summary>
	/// <returns></returns>
	ModelRender* GetModel()
	{
		return &m_playerModel;
	}

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

	/// <summary>
	/// 捕捉しているエネミーを取得
	/// </summary>
	Enemy*& GetTargetEnemy()
	{
		return m_enemy;
	}


	/// <summary>
	/// ダメージ処理
	/// </summary>
	void Damage(float damageAmount);

	/// <summary>
	/// 現在のHPを取得
	/// </summary>
	/// <returns></returns>
	float GetNowHp();

	void Init();

	//アニメーションイベント用関数
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

private:
	ModelRender m_playerModel;		//プレイヤーのモデル
	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップ

	CharacterController m_charaCon;	//キャラクターコントローラー
	EnPlayerState m_playerState = enIdle;	//プレイヤーの状態

	Vector3 m_position = Vector3::Zero;	//プレイヤーの座標
	Vector3 m_moveVec = Vector3::Zero;	//プレイヤーの移動ベクトル
	Quaternion m_rotation;	//プレイヤーの回転

	PlayerStateManager m_playerStateManager;	//プレイヤーステートマネージャー

	Enemy* m_enemy = nullptr;	//捕捉エネミー
	PlayerHpUI* m_hpUI = nullptr;

	EnPlayerAnimationEvent m_enAnimationEvent = enPlayerAnimationEvent_None;
};


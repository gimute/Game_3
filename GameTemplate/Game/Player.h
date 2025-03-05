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
		enAnimationClip_Walk,	//歩きアニメーション
		enAnimationClip_Run,	//ダッシュアニメーション
		enAnimationClip_Slash,	//斬撃モーション
		enAnimationClip_Guard,	//ガードモーション
		enAnimationClip_Backflip,	//バク転のモーション
		enAnimationClip_LeftDodge,	//左回避
		enAnimationClip_RightDodge,	//右回避
		enAnimationClip_ReceiveDamage,		//被ダメージ
		enAnimatinoClip_DamageGuard,	//ダメージガードモーション
		enAnimationClip_LeftGuardStrafe,	//ガード左移動
		enAnimationClip_RightGuardStrafe,	//ガード右移動
		enAnimationClip_JumpSlash,		//ジャンプ切り
		enAnimationClip_Die,			//しぼうアニメーション
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
	const Enemy*& GetLockOnEnemy()
	{
		return m_lockOnEnemy;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(Quaternion rotation)
	{
		m_rotation = rotation;
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

	/// <summary>
	/// ステータス等の初期化
	/// </summary>
	void InitStatus();

	//アニメーションイベント用関数
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	const bool IsEnemyLockOn() const
	{
		return m_isEnemyLockOn;
	}

	/// <summary>
	/// 敗北フラグをオン
	/// </summary>
	void PlayerLose()
	{
		m_loseFlag = true;
	}

	/// <summary>
	/// 敗北確認
	/// </summary>
	/// <returns></returns>
	const bool GetLoseFlag() const
	{
		return m_loseFlag;
	}

	/// <summary>
	/// エネミーリストの初期化
	/// </summary>
	/// <param name="enemyList"></param>
	void InitEnemyList(std::vector<Enemy*>& enemyList)
	{
		m_enemyList = &enemyList;
	}

	/// <summary>
	/// ロックオンエネミーを更新
	/// </summary>
	void LockOnEnemyUpdate();

private:

	ModelRender m_playerModel;		//プレイヤーのモデル

	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップ
	EnPlayerAnimationEvent m_enAnimationEvent = enPlayerAnimationEvent_None;	//アニメーションイベント

	CharacterController m_charaCon;	//キャラクターコントローラー
	EnPlayerState m_playerState = enPlayerIdle;	//プレイヤーの状態
	PlayerStateManager m_playerStateManager;	//プレイヤーステートマネージャー

	Vector3 m_position = Vector3::Zero;	//プレイヤーの座標
	Vector3 m_moveVec = Vector3::Zero;	//プレイヤーの移動ベクトル
	Quaternion m_rotation;	//プレイヤーの回転

	const std::vector<Enemy*>* m_enemyList;	//エネミーリスト
	const Enemy* m_lockOnEnemy = nullptr;	//捕捉エネミー

	PlayerHpUI* m_hpUI = nullptr;	//HPUI

	bool m_isEnemyLockOn = false;	//ロックオンフラグ
	bool m_loseFlag = false;	//敗北フラグ
};


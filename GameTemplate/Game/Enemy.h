#pragma once

#include "EnEnemyState.h"
#include "EnemyStateManager.h"

class EnemyHpUI;

//エネミー
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;


	//アニメーションクリップのアニメーション指定用のenum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//待機アニメーション
		enAnimationClip_Walk,	//歩行アニメーション
		enAnimationClip_BackWalk,	//後ろ歩きモーション
		enAnimationClip_Slash,	//斬撃モーション
		enAnimationClip_JumpSlash,	//ジャンプ切り
		enAnimationClip_Guard,	//ガードモーション
		enAnimatinoClip_DamageGuard,	//ダメージガードモーション
		enAnimationClip_Backflip,	//バク転のモーション
		enAnimationClip_DodgeLeft,	//左回避
		enAnimationClip_RightDodge,	//右回避
		enAnimationClip_LateralMovement_Left,	//左移動アニメーション
		enAnimationClip_LateralMovement_Right,	//右移動アニメーション
		enAnimationClip_ReceiveDamage,	//被ダメージモーション
		enAnimationClip_Die,			//しぼうアニメーション
		enAnimationClip_Num	//アニメーションの数
	};

	/// <summary>
	/// エネミーのポジションを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// エネミーのモデルレンダーを取得
	/// </summary>
	/// <returns></returns>
	ModelRender* GetModel()
	{
		return &m_enemyModel;
	}

	/// <summary>
	/// アニメーションイベント用関数
	/// </summary>
	/// <param name="clipName"></param>
	/// <param name="eventName"></param>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	//消去処理
	void Delete();

	/// <summary>
	/// ダメージ処理
	/// </summary>
	void Damage(float damageAmount);

	/// <summary>
	/// 現在のHPを取得
	/// </summary>
	/// <returns></returns>
	float GetNowHP();

	void HPUIInit();

private:
	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// モデルの初期化
	/// </summary>
	void InitModel();

	

private:
	ModelRender m_enemyModel;	//エネミーのモデル
	Vector3 m_position = Vector3::Zero;			//モデルの座標
	Quaternion m_rotation = Quaternion::Identity;		//モデルの回転
	CharacterController m_charaCon;	//モデルを動かすためのキャラコン

	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップ

	EnemyStateManager m_enemyStateManager;		

	EnEnemyAnimationEvent m_enAnimationEvent = enEnemyAnimationEvent_None;

	EnemyHpUI* m_enemyHpUI = nullptr;
};


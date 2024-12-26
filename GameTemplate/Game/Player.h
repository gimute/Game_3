#pragma once
//プレイヤークラス

#include "EnPlayerState.h"
#include "PlayerStateManager.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

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
	void Render(RenderContext& rc);

	//アニメーションクリップのアニメーション指定用のenum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//待機アニメーション
		enAnimationClip_Walk,	//歩行アニメーション
		enAnimationClip_Slash,	//斬撃モーション
		enAnimationClip_Guard,	//ガードモーション
		enAnimationClip_Backflip,	//バク転のモーション
		enAnimationClip_DodgeLeft,	//左回避
		enAnimationClip_DodgeRight,	//右回避
		enAnimationClip_Num	//アニメーションの数
	};

	

private:
	ModelRender m_playerModel;		//プレイヤーのモデル
	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップ

	CharacterController m_charaCon;	//キャラクターコントローラー
	EnPlayerState m_playerState = enIdle;	//プレイヤーの状態

	Vector3 m_position = Vector3::Zero;	//プレイヤーの座標
	Vector3 m_moveVec = Vector3::Zero;	//プレイヤーの移動ベクトル
	Quaternion m_rotation;	//プレイヤーの回転

	PlayerStateManager m_playerStateManager;	//プレイヤーステートマネージャー
};


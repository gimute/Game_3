#pragma once
//プレイヤークラス

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation();

	void PlayerModelUpdate();
	void Move();
	void Rotation();
	void PlayAnimation();

	void Render(RenderContext& rc);

	//アニメーションクリップのアニメーション指定用のenum
	enum EnAnimationClip {
		enAnimationClip_Idle,	//待機アニメーション
		enAnimationClip_Walk,	//歩行アニメーション
		enAnimationClip_Backflip,
		enAnimationClip_Num	//アニメーションの数
	};

	enum EnPlayerState {
		enIdle,		//待機
		enWalk,		//歩き
		enBackDodge		//後ろ回避
	};

private:
	ModelRender m_playerModel;		//プレイヤーのモデル
	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップ

	CharacterController m_charaCon;	//キャラクターコントローラー
	EnPlayerState m_playerState = enIdle;	//プレイヤーの状態

	Vector3 m_position = Vector3::Zero;	//プレイヤーの座標
	Vector3 m_moveVec = Vector3::Zero;	//プレイヤーの移動ベクトル
	Quaternion m_rotation;	//プレイヤーの回転

};


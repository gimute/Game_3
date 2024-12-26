#pragma once

#include "EnEnemyState.h"
#include "EnemyStateManager.h"

//エネミー
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
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
};


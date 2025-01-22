#pragma once
#include "IPlayerState.h"

//回避ステート
class PlayerStateDodge : public IPlayerState
{
	enum EnDodgeState
	{
		enBack,
		enLeft,
		enRight
	};

public:
	void Start(Player* player) override;
	void End(Player* player) override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

private:
	//回避方向のベクトルとステートを決定する関数
	void InitDodge(const Vector3& playerFront);


private:
	EnDodgeState m_dodgeState;		//回避方向ステート
	bool m_animationPlay = true;	//アニメーションが再生中か
	CollisionObject* m_dodgeCollision;	//回避判定用コリジョン
	Vector3 m_dodgeVec;	//回避ベクトル

	bool m_justDodge = false;	//ジャスト回避フラグ
	bool hitFlag = false;		//被ダメージフラグ
};


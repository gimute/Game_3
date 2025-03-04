#pragma once
#include "IPlayerState.h"


//走りステート
class PlayerStateRun : public IPlayerState
{
public:
	void Start(Player* player)override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void Rotation(Quaternion& rotation, const Vector3& position) override;
	void Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;
	EnPlayerState StateTransition() override;

private:
	Vector3 m_moveVec = Vector3::Zero;	//移動ベクトル
	bool hitFlag = false;		//被ダメージフラグ

};


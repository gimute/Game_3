#pragma once
#include "IPlayerState.h"

//バックフリップ(後ろ回避)
class PlayerStateBackflip : public IPlayerState
{
public:
	void Start(Player* payer);
	void End(Player* player);
	void Move(Vector3& position, CharacterController& charaCon) override;
	void AnimationPlay(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model) override;


public:
	bool m_anime = false;

	Vector3 m_playerBack = Vector3::Back;

	CollisionObject* m_avoidanceCollision;	//回避判定用コリジョン
};


#pragma once
#include "IPlayerState.h"

//アタックステート
class PlayerStateAttack : public IPlayerState
{
public:

	void Start(Player* player)override;
	void End(Player* player)override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;


private:
	bool m_animationPlay = true;	//アニメーション再生中フラグ
	int m_attackBoneID;		//攻撃判定コリジョンを生成するボーンのID

	CollisionObject* m_attackCollision;
};


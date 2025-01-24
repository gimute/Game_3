#pragma once
#include "IPlayerState.h"

//アタックステート
class PlayerStateAttack : public IPlayerState
{
public:

	void Start(Player* player)override;
	void End(Player* player)override;
	void Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;


private:
	bool m_animationPlay = true;	//アニメーション再生中フラグ
	int m_attackBoneID;		//攻撃コリジョンを生成するボーンのID

	CollisionObject* m_attackCollision;	//攻撃コリジョン

	bool hitFlag = false;		//被ダメージフラグ
	bool m_isAttackCollisionExistence = false;	//攻撃コリジョンが存在しているか

};


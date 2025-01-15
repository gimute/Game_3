#pragma once
#include "IPlayerState.h"


class Enemy;

//ジャスト回避後のラッシュ攻撃ステート
//まず敵に急接近しその後にラッシュを開始する

class PlayerStateJustDodgeAttack : public IPlayerState
{
public:
	enum AttackFlowState {
		enEnemyApproach,	//敵へ接近
		enAttack1,			//1つ目の攻撃
		enAttack2,			//2つ目の攻撃
		enAttack3,			//3つ目の攻撃
		enEnd				//終了
	};

	void Start(Player* player) override;
	void End(Player* player) override;
	void Move(Vector3& position, CharacterController& charaCon) override;
	void Rotation(Quaternion& rotation) override;
	void PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

private:
	void StateOenStep();

	CollisionObject* m_attackCollision;
	AttackFlowState m_attackFlowState = enEnemyApproach;
	int m_attackBoneID;		//攻撃判定コリジョンを生成するボーンのID

	Enemy* m_enemy;

	Vector3 playerToEnemyVec;
};


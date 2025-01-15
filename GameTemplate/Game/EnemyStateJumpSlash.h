#pragma once
#include "IEnemyState.h"

namespace {
	const wchar_t* ENEMY_ATTACK_COLLISION_BONE_NAME = L"mixamorig:RightHandMiddle1"; //攻撃判定コリジョンを生成するボーンの名前
}

//ジャンプ切りステート
class EnemyStateJumpSlash : public IEnemyState
{
public:
	//このステートに遷移する時の処理
	void Start(Enemy* enemy) override;

	//他のステートに遷移するときに行う後処理
	void End(Enemy* enemy) override;

	//移動処理
	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	//アニメーションの再生
	void Animation(ModelRender& model, EnEnemyAnimationEvent animeEvent) override;

	//コリジョン
	void Collision(const Vector3& pos, ModelRender& model) override;

	//ステート遷移
	EnEnemyState StateTransition() override;

private:
	bool m_isPlayAnimation = true;	//アニメーション再生中か

	int m_attackBoneID;		//攻撃判定コリジョンを生成するボーンのID
	CollisionObject* m_attackCollision;	//攻撃用コリジョン
};


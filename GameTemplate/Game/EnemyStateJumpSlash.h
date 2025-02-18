#pragma once
#include "IEnemyState.h"

//ジャンプ切りステート
class EnemyStateJumpSlash : public IEnemyState
{
public:
	//このステートに遷移する時の処理
	void Start(Enemy* enemy, Player* player) override;

	//他のステートに遷移するときに行う後処理
	void End(Enemy* enemy) override;

	//移動処理
	void Move(Vector3& position, CharacterController& charaCon, Player* player) override;

	//アニメーションの再生
	void Animation(ModelRender& model, EnEnemyAnimationEvent& animeEvent) override;

	//コリジョン
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;

	//ステート遷移
	EnEnemyState StateTransition() override;

private:
	bool m_isPlayAnimation = true;	//アニメーション再生中か

	int m_attackBoneID;		//攻撃判定コリジョンを生成するボーンのID
	CollisionObject* m_attackCollision;	//攻撃用コリジョン

	Vector3 m_targetPosition = Vector3::Zero;	//目標地点
	float m_MoveSpeed = 0.0f;		//移動速度

	bool m_hitFlag = false;		//被ダメージフラグ
	bool m_isAttackCollisionExistence = false;	//攻撃コリジョンが存在しているか
};


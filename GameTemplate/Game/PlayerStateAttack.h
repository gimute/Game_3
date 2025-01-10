#pragma once
#include "IPlayerState.h"
#include "EnPlayerState.h"

namespace {
	const wchar_t* PLAYER_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //攻撃判定コリジョンを生成するボーンの名前
}

//アタックステート
class PlayerStateAttack : public IPlayerState
{
public:

	void Start(Player* player)override;
	void PlayAnimation(ModelRender& model) override;
	EnPlayerState StateTransition() override;
	void Collision(const Vector3& pos, ModelRender& model, CharacterController& characon) override;


private:
	bool m_animationPlay = true;	//アニメーション再生中フラグ
	int m_attackBoneID;		//攻撃判定コリジョンを生成するボーンのID
};


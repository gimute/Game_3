#include "stdafx.h"
#include "PlayerStateBackflip.h"

#include "Player.h"

//ステート
void PlayerStateBackflip::Start(Player* player)
{
	m_playerBack = Vector3::Back;

	//プレイヤーの背面ベクトルをモデルの回転から求める
	player->GetModel()->GetRotation().Apply(m_playerBack);

	m_playerBack *= 100.0f;

	m_avoidanceCollision = NewGO<CollisionObject>(0);

	//コリジョンの位置を調整
	//モデルもモーションも仮なのでとりあえず適当に
	Vector3 collisionPos = player->GetPosition();
	collisionPos.y += 50.0f;
	

	m_avoidanceCollision->CreateBox(collisionPos, Quaternion::Identity, Vector3(100.0f, 150.0f, 100.0f));

	m_avoidanceCollision->SetIsEnableAutoDelete(false);

	m_avoidanceCollision->SetName("verticalAvoidance");
}

void PlayerStateBackflip::End(Player* player)
{
	DeleteGO(m_avoidanceCollision);
	m_avoidanceCollision = nullptr;
}

void PlayerStateBackflip::Move(Vector3& position, CharacterController& charaCon)
{
	position = charaCon.Execute(m_playerBack, g_gameTime->GetFrameDeltaTime());
}

void PlayerStateBackflip::AnimationPlay(ModelRender& model)
{
	if (model.IsPlayingAnimation())
	{
		model.PlayAnimation(Player::enAnimationClip_Backflip, 0.1f);
	}
	else
	{
		m_anime = true;
	}
}

EnPlayerState PlayerStateBackflip::StateTransition()
{
	if (m_anime)
	{
		m_anime = false;

		return enIdle;
	}
	else
	{
		return enBackflip;
	}

}

void PlayerStateBackflip::Collision(const Vector3& pos, ModelRender& model)
{

}


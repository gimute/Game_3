#include "stdafx.h"
#include "GameCamera.h"

#include "Player.h"
#include "Enemy.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");

	m_targetToCameraPos.Set(0.0f, 150.0f, -300.0f);
	m_defaultTargetToPositionLenge = m_targetToCameraPos.Length();
	/*g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);*/

	return true;
}

void GameCamera::Update()
{
	//計算前のカメラのポジション
	Vector3 toCameraPosOld = m_targetToCameraPos;

	if (m_player->IsEnemyLockOn())
	{
		Enemy* targetEnemy = m_player->GetTargetEnemy();

		//プレイヤーからエネミーに伸びるベクトル
		Vector3 playerToEnemyVec = (targetEnemy->GetPosition() - m_player->GetPosition());

		//注視点とカメラの距離の調整
		float playerToEnemyVecLenge = playerToEnemyVec.Length();

		Vector3 newTargetToCameraPos = m_targetToCameraPos;
	
		if (m_defaultTargetToPositionLenge < playerToEnemyVecLenge)
		{
			//画角に敵とプレイヤーが収まるように注視点とカメラの距離を調整
			newTargetToCameraPos *= playerToEnemyVecLenge / m_targetToCameraPos.Length();
		}
		m_targetToCameraPos.Lerp(0.15, m_targetToCameraPos, newTargetToCameraPos);

		//注視点の設定
		Vector3 newTargetPos = playerToEnemyVec / 2.0f + m_player->GetPosition();
		newTargetPos.y += 50.0f;

		m_targetPos.Lerp(0.15, m_targetPos, newTargetPos);

	}
	else
	{
		//注視点とカメラの距離をデフォルトに
		Vector3 newTargetToCameraPos = m_targetToCameraPos;
		newTargetToCameraPos *= m_defaultTargetToPositionLenge / m_targetToCameraPos.Length();

		m_targetToCameraPos.Lerp(0.15, m_targetToCameraPos, newTargetToCameraPos);

		//注視点の設定
		Vector3 newTargetPos = m_player->GetPosition();

		newTargetPos.y += 50.0f;

		m_targetPos.Lerp(0.15, m_targetPos, newTargetPos);
	}
		
	


	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_targetToCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_targetToCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_targetToCameraPos);

	Vector3 toPosDir = m_targetToCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < 0.1f) {
		//カメラが上向きすぎ。
		m_targetToCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.999f) {
		//カメラが下向きすぎ。
		m_targetToCameraPos = toCameraPosOld;
	}

	m_cameraPos = m_targetPos + m_targetToCameraPos;


	g_camera3D->SetTarget(m_targetPos);
	g_camera3D->SetPosition(m_cameraPos);

	g_camera3D->Update();
}

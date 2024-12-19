#include "stdafx.h"
#include "GameCamera.h"

#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");

	m_toTargetPos.Set(0.0f, 100.0f, -200.0f);
	/*g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);*/

	m_oldPlayerPos = m_player->GetPosition();
	m_oldPlayerPos.y = 0.0f;

	return true;
}

void GameCamera::Update()
{
	m_target = m_player->GetPosition();

	m_target.y += 50.0f;

	Vector3 toCameraPosOld = m_toTargetPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toTargetPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toTargetPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toTargetPos);

	Vector3 toPosDir = m_toTargetPos;
	toPosDir.Normalize();
	if (toPosDir.y < 0.1f) {
		//カメラが上向きすぎ。
		m_toTargetPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.999f) {
		//カメラが下向きすぎ。
		m_toTargetPos = toCameraPosOld;
	}

	m_pos = m_target + m_toTargetPos;


	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(m_pos);

	g_camera3D->Update();
}

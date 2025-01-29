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

	m_targetToCameraVec.Set(0.0f, 150.0f, -300.0f);
	m_defaultTargetToPositionLenge = m_targetToCameraVec.Length();
	/*g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);*/

	return true;
}

void GameCamera::Update()
{
	//�v�Z�O�̃J�����̃|�W�V����
	Vector3 toCameraPosOld = m_targetToCameraVec;

	//�����_
	if (m_player->IsEnemyLockOn())
	{
		Enemy* targetEnemy = m_player->GetTargetEnemy();

		const Vector3 playerToEnemyVec = (targetEnemy->GetPosition() - m_player->GetPosition());

		//�����_����J�����ւ̃x�N�g��
		//���`��Ԃ������̂ŃR�s�[�����x�N�g���ɏ��������Ă���
		Vector3 newTargetToCameraPos = m_targetToCameraVec;

		//�v���C���[�ƃG�l�~�[��������ɕ���Ŏʂ�悤�ɒ����_����J�����ւ̃x�N�g������]������
		Quaternion cameraPosRotation;
		cameraPosRotation.SetRotation(newTargetToCameraPos, (playerToEnemyVec * -1 + Vector3::Up * 100.0f));
		cameraPosRotation.Apply(newTargetToCameraPos);

		//�����_�ƃJ�����̋����̒���
		float playerToEnemyVecLenge = playerToEnemyVec.Length();
		if (m_defaultTargetToPositionLenge < playerToEnemyVecLenge)
		{
			//��p�ɓG�ƃv���C���[�����܂�悤�ɒ����_�ƃJ�����̋����𒲐�
			newTargetToCameraPos *= playerToEnemyVecLenge / newTargetToCameraPos.Length();
		}
		else
		{
			newTargetToCameraPos *= m_defaultTargetToPositionLenge / newTargetToCameraPos.Length();
		}


		m_targetToCameraVec.Lerp(0.15, m_targetToCameraVec, newTargetToCameraPos);

		//�����_�̐ݒ�
		Vector3 newTargetPos = playerToEnemyVec / 2.0f + m_player->GetPosition();
		newTargetPos.y += 50.0f;
		m_targetPos.Lerp(0.15, m_targetPos, newTargetPos);

	}
	else
	{
		//�����_�ƃJ�����̋������f�t�H���g��
		Vector3 newTargetToCameraPos = m_targetToCameraVec;
		newTargetToCameraPos *= m_defaultTargetToPositionLenge / m_targetToCameraVec.Length();

		m_targetToCameraVec.Lerp(0.15, m_targetToCameraVec, newTargetToCameraPos);

		//�����_�̐ݒ�
		Vector3 newTargetPos = m_player->GetPosition();
		newTargetPos.y += 50.0f;
		m_targetPos.Lerp(0.15, m_targetPos, newTargetPos);
	}
		
	


	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y������̉�]
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_targetToCameraVec);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_targetToCameraVec);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_targetToCameraVec);

	Vector3 toPosDir = m_targetToCameraVec;
	toPosDir.Normalize();
	if (toPosDir.y < 0.01f) {
		//�J����������������B
		m_targetToCameraVec = toCameraPosOld;
		//int te = 1;
	}
	else if (toPosDir.y > 0.999f) {
		//�J�����������������B
		m_targetToCameraVec = toCameraPosOld;
		//int te = 1;

	}

	m_cameraPos = m_targetPos + m_targetToCameraVec;


	g_camera3D->SetTarget(m_targetPos);
	g_camera3D->SetPosition(m_cameraPos);

	g_camera3D->Update();
}

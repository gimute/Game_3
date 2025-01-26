#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;

private:
	Player* m_player = nullptr;
	Vector3 m_targetToCameraVec;					//�����_����J�����ւ̃x�N�g��
	float m_defaultTargetToPositionLenge = 0.0f;	//�f�t�H���g�̒����_����J�����ւ̋���
	Vector3 m_targetPos;
	Quaternion qRot;
	Vector3 m_cameraPos = Vector3::Zero;
};


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
	Vector3 m_targetToCameraVec;					//注視点からカメラへのベクトル
	float m_defaultTargetToPositionLenge = 0.0f;	//デフォルトの注視点からカメラへの距離
	Vector3 m_targetPos;
	Quaternion qRot;
	Vector3 m_cameraPos = Vector3::Zero;
};


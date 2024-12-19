#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:
	Player* m_player = nullptr;
	Vector3 m_toTargetPos;
	Vector3 m_target;
	Vector3 m_oldPlayerPos = Vector3::Zero;
	Quaternion qRot;
	Vector3 m_pos = Vector3::Zero;
};


#pragma once

class Enemy;

//�G�l�~�[�Ǘ��N���X
class EnemyManager : public IGameObject
{
public:
	~EnemyManager();

	void Update();

	/// <summary>
	/// �G�l�~�[��ǉ�
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	void NewGOEnemy(Vector3 pos, Quaternion rot);

	std::vector<Enemy*>& GetEnemyList()
	{
		return m_EnemyList;
	}

private:
	std::vector<Enemy*> m_EnemyList;

};


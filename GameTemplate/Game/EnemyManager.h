#pragma once

class Enemy;

//エネミー管理クラス
class EnemyManager : public IGameObject
{
public:
	~EnemyManager();

	void Update();

	/// <summary>
	/// エネミーを追加
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


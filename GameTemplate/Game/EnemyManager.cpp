#include "stdafx.h"
#include "EnemyManager.h"

#include "Enemy.h"

//エネミー管理クラス

EnemyManager::~EnemyManager()
{
	for (auto& enemy : m_EnemyList)
	{
		DeleteGO(enemy);
	}
}

void EnemyManager::Update()
{
	for (auto& enemy : m_EnemyList)
	{
		if (enemy->IsDead())
		{
			std::vector<Enemy*>::iterator it;

			it = std::find(m_EnemyList.begin(), m_EnemyList.end(), enemy);

			if (it != m_EnemyList.end())
			{
				m_EnemyList.erase(it);
			}
		}
	}
}

void EnemyManager::NewGOEnemy(Vector3 pos, Quaternion rot)
{
	m_EnemyList.push_back(NewGO<Enemy>(0, "enemy"));
	m_EnemyList.back()->Init(pos, rot);
}

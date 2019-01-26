#include "EnemyManager.h"

#include "Enemy.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
EnemyManager::EnemyManager(void)
{
	// ...
}

/**
 * @brief Destructor
 */
EnemyManager::~EnemyManager(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void EnemyManager::Initialize(void)
{
}

/**
 * @brief Release
 */
void EnemyManager::Release(void)
{
	int nEnemyCount = m_aEnemyList.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		m_aEnemyList[i].Release();
	}
	m_aEnemyList.Empty();
}

/**
 * @brief Update
 */
void EnemyManager::Update(float dt)
{
	int nEnemyCount = m_aEnemyList.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		m_aEnemyList[i].Update(dt);
	}
}

/**
 * @brief CreateEnemies
 */
void EnemyManager::CreateEnemies(int number)
{
	for (int i = 0; i < number; ++i)
	{
		Enemy enemy;
		//todo enemy.Initialize();
		m_aEnemyList.Add(enemy);
	}
}

/**
 * @brief GetEnemyList
 */
void EnemyManager::GetEnemyList(CShArray<Enemy*>& aEnemyList)
{
	int nEnemyCount = m_aEnemyList.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		aEnemyList.Add(&m_aEnemyList[i]);
	}
}

/**
 * @brief GetEnemyListInRange
 */
void EnemyManager::GetEnemyListInRange(CShArray<Enemy*>& aEnemyList, const CShVector3 & pos, float rangeMin, float rangeMax)
{
	float rangeMinSquared = rangeMin * rangeMin;
	float rangeMaxSquared = rangeMax * rangeMax;

	int nEnemyCount = m_aEnemyList.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		const CShVector3 & enemyPos = m_aEnemyList[i].GetPosition();

		if (enemyPos == pos)
			continue;

		float distSquared = Plugin::GetDistanceSquared(enemyPos, pos);
		
		if (distSquared <= rangeMaxSquared
			&& distSquared >= rangeMinSquared)
		{
			aEnemyList.Add(&m_aEnemyList[i]);
		}
	}
}

#include "EnemyManager.h"

#include "Enemy.h"

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
void EnemyManager::Initialize()
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
		m_aEnemyList[i]->Release();
		SH_SAFE_FREE(m_aEnemyList[i]);
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
		m_aEnemyList[i]->Update(dt);
	}
}

void EnemyManager::CreateEnemies(int number)
{
	for (int i = 0; i < number; ++i)
	{
		Enemy * pEnemy = new Enemy();
		//todo Enemy->Initialize();
		m_aEnemyList.Add(pEnemy);
	}
}

void EnemyManager::GetEnemyList(CShArray<Enemy*>& aEnemyList)
{
	int nEnemyCount = m_aEnemyList.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		aEnemyList.Add(m_aEnemyList[i]);
	}
}

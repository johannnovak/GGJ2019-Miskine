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
void EnemyManager::Initialize(const CShIdentifier & levelIdentifer)
{
	for (int i = 0; i < e_enemy_max; i++)
	{
		for (int j = 0; j < POOL_SIZE; j++)
		{
			int iHealth;
			char szSpriteIdentifier[1024];
			
			switch ((EEnemy)i)
			{
				case e_enemy_01 : 
				{
					sprintf(szSpriteIdentifier, "walk_01"); //TODO
					iHealth = 100;
				}
				break;

				default:
				{
					iHealth = 100;
					
				}
				break;
			}
			ShEntity2* pEntity = ShEntity2::Create(levelIdentifer, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("player"), CShIdentifier(szSpriteIdentifier), CShVector3(0.0f, 0.0f, 0.0f), CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f), false);
			m_aEnemy[i][j].Initialize(pEntity, iHealth);
			m_aiCurrentEnemy[i] = 0;
		}
	}
}

/**
 * @brief Release
 */
void EnemyManager::Release(void)
{
	for (int i = 0; i < e_enemy_max; i++)
	{
		for (int j = 0; j < POOL_SIZE; j++)
		{
			m_aEnemy[i][j].Release();
		}
	}

	m_apActiveEnemy.Empty();
}

/**
 * @brief Update
 */
void EnemyManager::Update(float dt)
{
	int nEnemyCount = m_apActiveEnemy.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		m_apActiveEnemy[i]->Update(dt);
	}
}

/**
 * @brief CreateEnemies
 */
void EnemyManager::SpawnEnemy(EEnemy eEnemy, const CShVector3 vPosition, int iCount)
{
	for (int i = 0; i < iCount; ++i)
	{
		Enemy * pEnemi = &m_aEnemy[eEnemy][m_aiCurrentEnemy[eEnemy]];

		m_aiCurrentEnemy[eEnemy]++;
		m_aiCurrentEnemy[eEnemy] %= POOL_SIZE;
		
		m_apActiveEnemy.Add(pEnemi);
		pEnemi->Start(vPosition);
	}
}

/**
 * @brief GetEnemyList
 */
void EnemyManager::GetEnemyList(CShArray<Enemy*>& aEnemyList)
{
	int nEnemyCount = m_apActiveEnemy.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		aEnemyList.Add(m_apActiveEnemy[i]);
	}
}

/**
 * @brief GetEnemyListInRange
 */
void EnemyManager::GetEnemyListInRange(CShArray<Enemy*>& aEnemyList, const CShVector3 & pos, float rangeMin, float rangeMax)
{
	float rangeMinSquared = rangeMin * rangeMin;
	float rangeMaxSquared = rangeMax * rangeMax;

	int nEnemyCount = m_apActiveEnemy.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		const CShVector3 & enemyPos = m_apActiveEnemy[i]->GetPosition();

		if (m_apActiveEnemy[i]->IsDead())
			continue;

		if (enemyPos == pos)
			continue;

		float distSquared = Plugin::GetDistanceSquared(enemyPos, pos);
		
		if (distSquared <= rangeMaxSquared
			&& distSquared >= rangeMinSquared)
		{
			aEnemyList.Add(m_apActiveEnemy[i]);
		}
	}
}

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
					sprintf(szSpriteIdentifier, "walk"); //TODO
					iHealth = 100;
				}
				break;

				default:
				{
					sprintf(szSpriteIdentifier, "walk");
					iHealth = 100;
				}
				break;
			}

			int id = 1;
			CShArray<ShEntity2 *> aEntityList;
			while (1)
			{
				char szFinalSpriteIdentifier[1024];
				sprintf(szFinalSpriteIdentifier, "%s_%02d", szSpriteIdentifier, id++);
				ShSprite * pSprite = ShSprite::Find(CShIdentifier("player"), CShIdentifier(szFinalSpriteIdentifier));
				if (shNULL == pSprite)
					break;
				ShEntity2 * pEntity = ShEntity2::Create(levelIdentifer, GID(NULL), CShIdentifier("layer_default"), pSprite, CShVector3(0.0f, 0.0f, 1.0f), CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f), false);
				aEntityList.Add(pEntity);
			}
			
			ShEntity2 * pEntityLifebar = ShEntity2::Create(levelIdentifer, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("game"), CShIdentifier("lifebar"), CShVector3(0.0f, 0.0f, 1.1f), CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f), false);
			ShEntity2::SetPivotCenterLeft(pEntityLifebar);
			ShEntity2::Link(aEntityList[0], pEntityLifebar);
			float fEntityHeight = ShEntity2::GetHeight(aEntityList[0]);
			float fEntityLifebarWidth = ShEntity2::GetWidth(pEntityLifebar);
			ShEntity2::SetRelativePosition2(pEntityLifebar, CShVector2(-fEntityLifebarWidth * 0.5f, fEntityHeight * 0.5f));	

			m_aEnemy[i][j].Initialize(aEntityList, pEntityLifebar, iHealth);
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
Enemy * EnemyManager::SpawnEnemy(EEnemy eEnemy, const CShVector3 & vPosition, const CShVector2 & vDestination)
{
	Enemy * pEnemy = &m_aEnemy[eEnemy][m_aiCurrentEnemy[eEnemy]];

	m_aiCurrentEnemy[eEnemy]++;
	m_aiCurrentEnemy[eEnemy] %= POOL_SIZE;
		
	m_apActiveEnemy.Add(pEnemy);
	pEnemy->Start(vPosition, vDestination);

	return pEnemy;
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

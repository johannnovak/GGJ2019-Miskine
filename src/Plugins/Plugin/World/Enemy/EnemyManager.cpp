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
					sprintf(szSpriteIdentifier, "spider");
					iHealth = 100;
				}
				break;

				default:
				{
					sprintf(szSpriteIdentifier, "spider");
					iHealth = 100;
				}
				break;
			}

			CShArray<ShEntity2 *> aEntityList[Enemy::state_max][Enemy::animation_max];
			char szDirection[32]; 
			for (int iState = 0; iState < Enemy::state_max; ++iState)
			{
				for (int iType = 0; iType < Enemy::animation_max; ++iType)
				{
					switch ((Enemy::EAnimationType)iType)
					{
					case Enemy::animation_top:sprintf(szDirection, "top"); break;
					case Enemy::animation_bottom:sprintf(szDirection, "bottom"); break;
					case Enemy::animation_left:sprintf(szDirection, "left"); break;
					case Enemy::animation_right:sprintf(szDirection, "right"); break;
					default: sprintf(szDirection, "bottom");
					}

					int id = 1;
					while (1)
					{
						char szFinalSpriteIdentifier[1024];
						switch ((Enemy::EAnimationState)iState)
						{
						case Enemy::state_cg: sprintf(szFinalSpriteIdentifier, "%s_cg_%s_%02d", szSpriteIdentifier, szDirection, id++); break;
						default: sprintf(szFinalSpriteIdentifier, "%s_%s_%02d", szSpriteIdentifier, szDirection, id++);
						}

						ShSprite * pSprite = ShSprite::Find(CShIdentifier("game"), CShIdentifier(szFinalSpriteIdentifier));
						if (shNULL == pSprite)
							break;
						ShEntity2 * pEntity = ShEntity2::Create(levelIdentifer, GID(NULL), CShIdentifier("layer_default"), pSprite, CShVector3(0.0f, 0.0f, 2.0f), CShEulerAngles::ZERO, CShVector3(0.3f, 0.3f, 1.0f), false);
						aEntityList[iState][iType].Add(pEntity);
					}

				}
			}

			ShEntity2 * pEntityLifebar = ShEntity2::Create(levelIdentifer, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("game"), CShIdentifier("lifebar"), CShVector3::ZERO, CShEulerAngles::ZERO, CShVector3(0.4f, 0.4f, 1.0f), false);
			ShEntity2::SetPivotCenterLeft(pEntityLifebar);
			ShEntity2::Link(aEntityList[0][0][0], pEntityLifebar);
			float fEntityHeight = ShEntity2::GetHeight(aEntityList[0][0][0]) * ShEntity2::GetScale(aEntityList[0][0][0]).m_y;
			float fEntityLifebarWidth = ShEntity2::GetWidth(pEntityLifebar) * ShEntity2::GetScale(aEntityList[0][0][0]).m_x;
			ShEntity2::SetRelativePosition2(pEntityLifebar, CShVector2(-fEntityLifebarWidth * 0.5f, fEntityHeight + 10.0f));	

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
	CShArray<Enemy *> apEnemyToRemove;

	int nEnemyCount = m_apActiveEnemy.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		m_apActiveEnemy[i]->Update(dt);

		if (m_apActiveEnemy[i]->GetState() == Enemy::e_state_off)
		{
			apEnemyToRemove.Add(m_apActiveEnemy[i]);
		}
	}

	for (int i = 0; i < apEnemyToRemove.GetCount(); i++)
	{
		m_apActiveEnemy.RemoveAll(apEnemyToRemove[i]);
	}
}

/**
 * @brief CreateEnemies
 */
Enemy * EnemyManager::SpawnEnemy(EEnemy eEnemy, const CShVector2 & vPosition, const CShVector2 & vDestination, float fSpeed)
{
	Enemy * pEnemy = &m_aEnemy[eEnemy][m_aiCurrentEnemy[eEnemy]];

	m_aiCurrentEnemy[eEnemy]++;
	m_aiCurrentEnemy[eEnemy] %= POOL_SIZE;
		
	m_apActiveEnemy.Add(pEnemy);
	pEnemy->Start(vPosition, vDestination, fSpeed);

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
void EnemyManager::GetEnemyListInRange(CShArray<Enemy*>& aEnemyList, const CShVector2 & pos, float rangeMin, float rangeMax)
{
	float rangeMinSquared = rangeMin * rangeMin;
	float rangeMaxSquared = rangeMax * rangeMax;

	int nEnemyCount = m_apActiveEnemy.GetCount();
	for (int i = 0; i < nEnemyCount; ++i)
	{
		const CShVector2 & enemyPos = m_apActiveEnemy[i]->GetPosition();

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

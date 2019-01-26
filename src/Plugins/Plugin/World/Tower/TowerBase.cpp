#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy/EnemyManager.h"
#include "../Enemy/Enemy.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerBase::TowerBase(void)
: m_eTowerType(tower_pere)
, m_eTowerAttackType(tower_melee)
, m_eFocusType(focus_nearest)
, m_vPosition(CShVector2::ZERO)
, m_fRadiusMin(0.0f)
, m_fRadiusMax(100.0f)
, m_pDebugRadiusMin(shNULL)
, m_pDebugRadiusMax(shNULL)
, m_damages(0)
, m_bIsAttacking(false)
, m_fAttackCooldown(0.0f)
, m_fAttackSpeed(0.0f)
, m_level(0)
, m_pEnemyManager(shNULL)
, m_pCurrentTarget(shNULL)
, m_fAOERange(-1.0f)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.0f)
, m_currentSprite(0)
, m_aAttackAnimation()
{

}

/**
 * @brief Destructor
 */
TowerBase::~TowerBase(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerBase::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_levelIdentifier = levelIdentifier;

	m_eTowerType = towerType;
	m_eFocusType = focusType;
	m_vPosition = position;
	m_damages = damages;
	m_fAttackSpeed = attackSpeed;

	m_pEnemyManager = pEnemyManager;
	SH_ASSERT(shNULL != m_pEnemyManager);
	
	m_fAOERange = rangeAOE;
	m_fAnimationSpeed = 0.5f;

	m_pDebugRadiusMin = ShPrimitiveCircle::Create(m_levelIdentifier, CShIdentifier("rangeMin"), CShVector3(m_vPosition,0.0f), m_fRadiusMin, 8, CShRGBAf_RED);
	SH_ASSERT(shNULL != m_pDebugRadiusMin);
	ShPrimitiveCircle::Set2d(m_pDebugRadiusMin, true);
	m_pDebugRadiusMax = ShPrimitiveCircle::Create(m_levelIdentifier, CShIdentifier("rangeMax"), CShVector3(m_vPosition, 0.0f), m_fRadiusMax, 8, CShRGBAf_RED);
	SH_ASSERT(shNULL != m_pDebugRadiusMax);
	ShPrimitiveCircle::Set2d(m_pDebugRadiusMax, true);
}

/**
 * @brief Release
 */
void TowerBase::Release(void)
{
	ShPrimitiveCircle::Destroy(m_pDebugRadiusMin);
	ShPrimitiveCircle::Destroy(m_pDebugRadiusMax);

	for (int i = 0; i < direction_max; ++i)
	{
		int nAttackAnimCount = m_aAttackAnimation[i].GetCount();
		for (int j = 0; j < nAttackAnimCount; ++j)
		{
			ShEntity2::Destroy(m_aAttackAnimation[i][j]);
		}
		m_aAttackAnimation[i].Empty();
	}
}

/**
 * @brief Update
 */
void TowerBase::Update(float dt)
{
	if (m_bIsAttacking)
	{
		m_fAnimationDt += dt;
		if (m_fAnimationDt >= m_fAnimationSpeed)
		{
			m_fAnimationDt = 0.0f;
			// TODO Animate

			// TODO if animation ended
			{ // Attack ended
				if (m_pCurrentTarget->IsDead())
				{
					m_pCurrentTarget = shNULL;
				}
				else
				{
					if (-1 != m_fAOERange)
					{ // Hit enemies in currentTarget range
						const CShVector2 & targetPos = m_pCurrentTarget->GetPosition();

						CShArray<Enemy*> aEnemyList;
						m_pEnemyManager->GetEnemyListInRange(aEnemyList, targetPos, 0.0f, m_fAOERange);

						int nEnemyCount = aEnemyList.GetCount();
						for (int i = 0; i < nEnemyCount; ++i)
						{
							// Damages / 2
							aEnemyList[i]->TakeDamages(m_damages * 0.5f);
						}
					}

					m_pCurrentTarget->TakeDamages(m_damages);
					if (m_pCurrentTarget->IsDead())
					{
						m_pCurrentTarget = shNULL;
					}

				}

				m_bIsAttacking = false;
				m_fAttackCooldown = 0.0f;
			}
		}
	}
	else
	{
		m_fAttackCooldown += dt;

		if (m_fAttackCooldown >= m_fAttackSpeed)
		{
			if (m_pCurrentTarget)
			{
				const CShVector2 & targetPos = m_pCurrentTarget->GetPosition();

				float distSquared = Plugin::GetDistanceSquared(m_vPosition, targetPos);
				if (distSquared > m_fRadiusMax * m_fRadiusMax
					|| distSquared < m_fRadiusMin * m_fRadiusMin)
				{// Lost focus
					SH_TRACE("FOCUS LOST\n");
					m_pCurrentTarget = shNULL;
				}
			}

			if (shNULL == m_pCurrentTarget)
			{
				// Find potential enemy based on focus type
				CShArray<Enemy *> aEnemyList;
				m_pEnemyManager->GetEnemyListInRange(aEnemyList, m_vPosition, m_fRadiusMin, m_fRadiusMax);

				int currentId = -1;
				int health = -1;
				float distSquared = m_fRadiusMax * m_fRadiusMax;
				int nEnemyCount = aEnemyList.GetCount();
				for (int i = 0; i < nEnemyCount; ++i)
				{
					Enemy * pEnemy = aEnemyList[i];

					switch (m_eFocusType)
					{
					case focus_nearest:
					{
						const CShVector2 & enemyPos = pEnemy->GetPosition();
						float dist = Plugin::GetDistanceSquared(m_vPosition, enemyPos);

						if (dist < distSquared)
						{
							currentId = i;
							distSquared = dist;
						}
					}
					break;

					case focus_biggest_lifebase:
					{
						int enemyHealth = pEnemy->GetBaseHealth();
						if (enemyHealth > health)
						{
							currentId = i;
							health = enemyHealth;
						}
					}
					break;

					case focus_lowest_life:
					{
						int enemyHealth = pEnemy->GetCurrentHealth();
						if (enemyHealth == -1 || enemyHealth < health)
						{
							currentId = i;
							health = enemyHealth;
						}
					}
					break;
					}
				}

				if (-1 != currentId)
				{
					m_pCurrentTarget = aEnemyList[currentId];
					SH_TRACE("FOCUS TARGET\n");
				}
			}

			if (m_pCurrentTarget)
			{
				// Shoot target
				m_bIsAttacking = true;
				SH_TRACE("ATTACK TARGET\n");
			}
		}
	}
}

/**
 * @brief LevelUp
 */
void TowerBase::LevelUp(void)
{
	m_level++;
	m_damages += 10;
	m_fAttackSpeed -= 1.0f;
	// Ranges ?
}

/**
 * @brief GetCurrentLevel
 */
int TowerBase::GetCurrentLevel(void)
{
	return m_level;
}

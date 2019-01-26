#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy/EnemyManager.h"
#include "../Enemy/Enemy.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerBase::TowerBase(void)
: m_eTowerType(tower_melee)
, m_eFocusType(focus_nearest)
, m_vPosition(CShVector3::ZERO)
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
void TowerBase::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, ETowerType towerType, EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
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

	if (m_eTowerType == ETowerType::tower_melee)
	{
		m_fRadiusMin = 0.0f;
		m_fRadiusMax = 500.0f;
	}
	else
	{
		m_fRadiusMin = 50.0f;
		m_fRadiusMax = 300.0f;
	}

	ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("player"), CShIdentifier("walk_01"), m_vPosition, CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
	SH_ASSERT(shNULL != pEntity);
}

/**
 * @brief Release
 */
void TowerBase::Release(void)
{
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
				if (!m_pCurrentTarget->IsDead())
				{
					m_pCurrentTarget->TakeDamages(m_damages);
					if (-1 != m_fAOERange)
					{ // Hit enemies in currentTarget range
						const CShVector3 & targetPos = m_pCurrentTarget->GetPosition();

						CShArray<Enemy*> aEnemyList;
						m_pEnemyManager->GetEnemyListInRange(aEnemyList, targetPos, 0.0f, m_fAOERange);

						int nEnemyCount = aEnemyList.GetCount();
						for (int i = 0; i < nEnemyCount; ++i)
						{
							// Damages / 2 ?
							aEnemyList[i]->TakeDamages(m_damages * 0.5f);
						}
					}
				}
				else
				{
					m_pCurrentTarget = shNULL;
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
				const CShVector3 & targetPos = m_pCurrentTarget->GetPosition();

				float distSquared = Plugin::GetDistanceSquared(m_vPosition, targetPos);
				if (distSquared > m_fRadiusMax * m_fRadiusMax
					|| distSquared < m_fRadiusMin * m_fRadiusMin)
				{// Lost focus
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
						const CShVector3 & enemyPos = pEnemy->GetPosition();
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

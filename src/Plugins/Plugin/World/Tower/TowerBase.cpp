#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy/EnemyManager.h"
#include "../Enemy/Enemy.h"

/**
 * @brief Constructor
 */
TowerBase::TowerBase(void)
: m_eTowerType(tower_melee)
, m_eFocusType(focus_nearest)
, m_vPosition(CShVector3::ZERO)
, m_fDamages(0.0f)
, m_fAttackCooldown(0.0f)
, m_fAttackSpeed(0.0f)
, m_level(0)
, m_pEnemyManager(shNULL)
, m_pCurrentTarget(shNULL)
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
void TowerBase::Initialize(EnemyManager * pEnemyManager, ETowerType towerType, EFocusType focusType, const CShVector3 & position, float damages, float attackSpeed)
{
	m_eTowerType = towerType;
	m_eFocusType = focusType;
	m_vPosition = position;
	m_fDamages = damages;
	m_fAttackSpeed = attackSpeed;

	m_pEnemyManager = pEnemyManager;
	SH_ASSERT(shNULL != m_pEnemyManager);

	m_fAnimationSpeed = 0.5f;
}

/**
 * @brief Release
 */
void TowerBase::Release(void)
{
	if (m_eTowerType == ETowerType::tower_melee)
	{
		m_fRadiusMin = 0.0f;
		m_fRadiusMax = 10.0f;
	}
	else
	{
		m_fRadiusMin = 0.0f;
		m_fRadiusMax = 20.0f;
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
		{ // Attack ended
			m_bIsAttacking = false;
			m_fAnimationDt = 0.0f;
			m_pCurrentTarget->TakeDamages(m_fDamages);
		}
	}
	else
	{
		m_fAttackCooldown += dt;

		if (m_fAttackCooldown >= m_fAttackSpeed)
		{
			m_fAttackCooldown = 0.0f;

			if (m_pCurrentTarget)
			{				
				const CShVector3 & targetPos = m_pCurrentTarget->GetPosition();

				float distSquared = GetDistanceSquared(targetPos);
				if (distSquared > m_fRadiusMax * m_fRadiusMax
					|| distSquared < m_fRadiusMin * m_fRadiusMin)
				{// Lost focus
					m_pCurrentTarget = shNULL;

					// Find potential enemy based on focus type
					CShArray<Enemy *> aEnemyList;
					m_pEnemyManager->GetEnemyList(aEnemyList);

					int currentId = -1;
					int health = -1;
					float distSquared = m_fRadiusMax;
					int nEnemyCount = aEnemyList.GetCount();
					for (int i = 0; i < nEnemyCount; ++i)
					{
						const Enemy * pEnemy = aEnemyList[i];

						switch (m_eFocusType)
						{
							case focus_nearest:
							{
								const CShVector3 & enemyPos = pEnemy->GetPosition();
								float dist = GetDistanceSquared(enemyPos);
								
								if (dist <= m_fRadiusMax * m_fRadiusMax
									|| dist >= m_fRadiusMin * m_fRadiusMin)
								{
									if (dist < distSquared)
									{
										currentId = i;
										distSquared = dist;
									}
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
				}
			}

			if (m_pCurrentTarget)
			{
				// Shoot target
				m_bIsAttacking = true;
			}
		}
	}
}

float TowerBase::GetDistanceSquared(const CShVector3 & dest)
{
	//TODO Test me

	CShVector2 A(dest.m_x, dest.m_y);
	CShVector2 B(m_vPosition.m_x, m_vPosition.m_y);
	CShVector2 delta = A - B;

	return delta.DotProduct(delta);
}

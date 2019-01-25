#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
TowerBase::TowerBase(ETowerType towerType, EFocusType focusType, float damage, float attackSpeed)
: m_eTowerType(towerType)
, m_eFocusType(focusType)
, m_fDamage(damage)
, m_fAttackCooldown(0.0f)
, m_fAttackSpeed(attackSpeed)
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
void TowerBase::Initialize(void)
{
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

	}
	else
	{
		m_fAttackCooldown += dt;

		if (m_fAttackCooldown >= m_fAttackSpeed)
		{
			m_fAttackCooldown = 0.0f;

			if (m_pCurrentTarget)
			{
				// Check lost focus

				// if lost focus
					// m_pCurrentTarget = shNULL
					// Find potential enemy based on focus Type
			}

			if (m_pCurrentTarget)
			{
				// Shoot target
				m_bIsAttacking = true;
			}
		}
	}
}

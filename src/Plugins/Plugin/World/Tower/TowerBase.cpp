#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy.h"

/**
 * @brief Constructor
 */
TowerBase::TowerBase(void)
: m_eTowerType(tower_melee)
, m_eFocusType(focus_nearest)
, m_fDamages(0.0f)
, m_fAttackCooldown(0.0f)
, m_fAttackSpeed(0.0f)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.0f)
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
void TowerBase::Initialize(ETowerType towerType, EFocusType focusType, float damages, float attackSpeed)
{
	m_eTowerType = towerType;
	m_eFocusType = focusType;
	m_fDamages = damages;
	m_fAttackSpeed = attackSpeed;
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

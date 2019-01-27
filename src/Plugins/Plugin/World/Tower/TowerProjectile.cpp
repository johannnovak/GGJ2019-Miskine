#include "TowerProjectile.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerProjectile::TowerProjectile(void)
: m_fSpeed(0.0f)
, m_vPosition()
, m_pTarget(shNULL)
, m_pEntity(shNULL)
{
}

/**
 * @brief Destructor
 */
TowerProjectile::~TowerProjectile(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerProjectile::Initialize(const CShVector2 & pos, float speed, Enemy * pTarget, ShEntity2 * pEntity)
{
	m_fSpeed = speed;
	m_vPosition = pos;
	m_pTarget = pTarget;
}

/**
 * @brief Release
 */
void TowerProjectile::Release(void)
{
	ShEntity2::Destroy(m_pEntity);
}

/**
 * @brief Update
 */
bool TowerProjectile::Update(float dt)
{
	// Move


	// Check if projectile hited its target
	const CShVector2 & targetPos = m_pTarget->GetPosition();
	float distSquared = Plugin::GetDistanceSquared(m_vPosition, targetPos);
	if (distSquared < 100.0f)
	{
		return true;
	}

	return false;
}

Enemy * TowerProjectile::GetTarget(void)
{
	return m_pTarget;
}

const CShVector2 & TowerProjectile::GetPosition(void) const
{
	return m_vPosition;
}

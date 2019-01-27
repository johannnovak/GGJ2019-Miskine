#include "TowerProjectile.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerProjectile::TowerProjectile(void)
: m_fSpeed(0.0f)
, m_vPosition(CShVector2::ZERO)
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
	m_pEntity = pEntity;
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
	const CShVector2 & targetPos = m_pTarget->GetPosition();

	float u_x = targetPos.m_x - m_vPosition.m_x, u_y = targetPos.m_y - m_vPosition.m_y;
	float u = sqrt((u_x*u_x) + (u_y*u_y));
	float v_x = (1 / u) * u_x;
	float v_y = (1 / u) * u_y;

	m_vPosition.m_x += v_x * m_fSpeed;
	m_vPosition.m_y += v_y * m_fSpeed;

	ShEntity2::SetPosition2(m_pEntity, m_vPosition);

	float distSquared = Plugin::GetDistanceSquared(m_vPosition, targetPos);
	if (distSquared < 100.0f)
	{
		return true;
	}

	CShEulerAngles angle = ShEntity2::GetRotation(m_pEntity);
	angle.m_z -= 0.01f * 60.0f * dt;
	ShEntity2::Rotate(m_pEntity, angle);

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

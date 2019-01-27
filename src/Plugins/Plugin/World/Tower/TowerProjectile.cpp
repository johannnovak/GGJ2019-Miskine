#include "TowerProjectile.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerProjectile::TowerProjectile(void)
: m_fSpeed(0.0f)
, m_fCompletion(0.0f)
, m_v(CShVector2::ZERO)
, m_vStartPosition(CShVector2::ZERO)
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
	m_fCompletion = 0.0f;
	m_pTarget = pTarget;
	m_vStartPosition = m_vPosition;
	m_v = m_pTarget->GetPosition() - m_vPosition;
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
	m_fCompletion += dt * (200.0f / (1.0f + m_v.GetLength()));

	if (m_fCompletion < 1.0f)
	{
		m_vPosition.m_x = m_vStartPosition.m_x + m_fCompletion * m_v.m_x;
		m_vPosition.m_y = m_vStartPosition.m_y + m_fCompletion * m_v.m_y;
		ShEntity2::SetPosition2(m_pEntity, m_vPosition);
	}
	else
	{
		m_vPosition.m_x = m_vStartPosition.m_x + m_v.m_x;
		m_vPosition.m_y = m_vStartPosition.m_y + m_v.m_y;
		ShEntity2::SetPosition2(m_pEntity, m_vPosition);

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

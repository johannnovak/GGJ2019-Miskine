#include "Enemy.h"

/**
 * @brief Constructor
 */
Enemy::Enemy(void)
: m_pEntity(shNULL)
, m_vPosition(CShVector3::ZERO)
, m_health(0)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.0f)
, m_aMoveAnimation()
{
	// ...
}

/**
 * @brief Destructor
 */
Enemy::~Enemy(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void Enemy::Initialize(const CShIdentifier & levelIdentifier, const CShIdentifier & spriteIdentifier, const CShVector3 & position, int health)
{
	m_pEntity = ShEntity2::Find(levelIdentifier, spriteIdentifier);
	SH_ASSERT(shNULL != m_pEntity);

	m_vPosition = position;
	m_health = health;
}

/**
 * @brief Release
 */
void Enemy::Release(void)
{

}

/**
 * @brief Update
 */
void Enemy::Update(float dt)
{
	// Move

	// Update anim
	m_fAnimationDt += dt;
	if (m_fAnimationDt >= m_fAnimationSpeed)
	{

	}
}

void Enemy::TakeDamages(float damages)
{
	m_health -= damages;
	if (0 > m_health)
	{ // Dead
		
	}
}

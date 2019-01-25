#include "Enemy.h"

/**
 * @brief Constructor
 */
Enemy::Enemy(void)
: m_pEntity(shNULL)
, m_health(0)
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
void Enemy::Initialize(const CShIdentifier & levelIdentifier, const CShIdentifier & spriteIdentifier, int health)
{
	m_pEntity = ShEntity2::Find(levelIdentifier, spriteIdentifier);
	SH_ASSERT(shNULL != m_pEntity);

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
}

void Enemy::TakeDamages(float damages)
{
	m_health -= damages;
	if (0 > m_health)
	{ // Dead
		
	}
}

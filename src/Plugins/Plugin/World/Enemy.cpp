#include "ShSDK/ShSDK.h"
#include "Enemy.h"

/**
 * @brief Constructor
 */
Enemy::Enemy(void)
: m_pEntity(shNULL)
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
 * @param pUser
 */
void Enemy::Initialize(const CShIdentifier & levelIdentifier, const CShIdentifier & spriteIdentifier, ShPath * pPath)
{
	m_pEntity = ShEntity2::Find(levelIdentifier, spriteIdentifier);
	SH_ASSERT(shNULL != m_pEntity);

	m_pPath = pPath;
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
static float fTime = 0.0f;
void Enemy::Update(float dt)
{
	fTime += 0.1f * dt;
	CShVector3 newPos = ShPath::GetPositionAtTime(m_pPath, fTime);
	ShEntity2::SetWorldPosition(m_pEntity, newPos);
}

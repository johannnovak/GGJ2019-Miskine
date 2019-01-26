#include "TowerRange.h"
#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy/EnemyManager.h"

/**
 * @brief Constructor
 */
TowerRange::TowerRange(void)
: TowerBase()
{

}

/**
 * @brief Destructor
 */
TowerRange::~TowerRange(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerRange::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_eTowerType = tower_range;

	m_fRadiusMin = 50.0f;
	m_fRadiusMax = 300.0f;

	TowerBase::Initialize(levelIdentifier, pEnemyManager, focusType, position, damages, attackSpeed, rangeAOE);	

	ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("player"), CShIdentifier("walk_01"), CShVector3(m_vPosition, 10.0f), CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
	SH_ASSERT(shNULL != pEntity);
	m_aAttackAnimation.Add(pEntity);

	// Create m_pProjectile
}

/**
 * @brief Release
 */
void TowerRange::Release(void)
{
	ShEntity2::Destroy(m_pProjectile);

	TowerBase::Release();
}

/**
 * @brief Update
 */
void TowerRange::Update(float dt)
{
	TowerBase::Update(dt);
	
	// Update projectile or rewrite Base Update here
}

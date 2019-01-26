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
void TowerRange::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_eTowerAttackType = tower_range;

	m_fRadiusMin = 50.0f;
	m_fRadiusMax = 300.0f;

	TowerBase::Initialize(levelIdentifier, pEnemyManager, towerType, focusType, position, damages, attackSpeed, rangeAOE);	

	ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("player"), CShIdentifier("walk_01"), m_vPosition, CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
	SH_ASSERT(shNULL != pEntity);
	//m_aAttackAnimation.Add(pEntity);

		char szSpriteIdentifier[1024];
			
	switch (towerType)
	{
		case tower_pere : sprintf(szSpriteIdentifier, "fille"); break;
		case tower_mere: sprintf(szSpriteIdentifier, "fils"); break;
		default: sprintf(szSpriteIdentifier, "fils"); break;
	}

	char szDirection[32];

	for (int i = 0; i < animation_max; ++i)
	{
		switch ((EAnimationType)i)
		{
			case animation_top:sprintf(szDirection, "attack_back"); break;
			case animation_bottom:sprintf(szDirection, "attack_front"); break;
			case animation_left:sprintf(szDirection, "attack_left"); break;
			case animation_right:sprintf(szDirection, "attack_right"); break;
			case animation_idle:sprintf(szDirection, "idle"); break;
			default: SH_ASSERT_ALWAYS();
		}

		int id = 1;
		CShArray<ShEntity2 *> aEntityList;
		while (1)
		{
			char szFinalSpriteIdentifier[1024];
			sprintf(szFinalSpriteIdentifier, "%s_%s_%02d", szSpriteIdentifier, szDirection, id++);
			ShSprite * pSprite = ShSprite::Find(CShIdentifier("game"), CShIdentifier(szFinalSpriteIdentifier));
			if (shNULL == pSprite)
				break;
			ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), pSprite, position, CShEulerAngles::ZERO, CShVector3(0.4f, 0.4f, 1.0f), false);
			aEntityList.Add(pEntity);
		}
		m_aAttackAnimation[i] = aEntityList;
	}

	ShEntity2::SetShow(m_aAttackAnimation[m_currentAnimationType][m_currentSprite], true);

	// Create m_pProjectile
	// @ TODO
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

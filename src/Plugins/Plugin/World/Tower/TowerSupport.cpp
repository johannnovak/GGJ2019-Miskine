#include "TowerSupport.h"
#include "TowerBase.h"

#include "../Enemy/EnemyManager.h"

/**
 * @brief Constructor
 */
TowerSupport::TowerSupport()
{

}

/**
 * @brief Destructor
 */
TowerSupport::~TowerSupport(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerSupport::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_eTowerAttackType = tower_support;

	m_fRadiusMin = 10.0f;
	m_fRadiusMax = 200.0f;

	TowerBase::Initialize(levelIdentifier, pEnemyManager, towerType, focusType, position, damages, attackSpeed, rangeAOE);	

	char szSpriteIdentifier[1024];
			
	switch (towerType)
	{
		case tower_fille : sprintf(szSpriteIdentifier, "fille"); break;
		default: sprintf(szSpriteIdentifier, "fille"); break;
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
			ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), pSprite, CShVector3(position, 10.0f), CShEulerAngles::ZERO, CShVector3(0.4f, 0.4f, 1.0f), false);
			aEntityList.Add(pEntity);
		}
		m_aAttackAnimation[i] = aEntityList;
	}

	ShEntity2::SetShow(m_aAttackAnimation[m_eCurrentAnimationType][m_currentSprite], true);
}

/**
 * @brief Release
 */
void TowerSupport::Release(void)
{
	TowerBase::Release();
}

/**
 * @brief Update
 */
void TowerSupport::Update(float dt)
{
	m_fAnimationDt += dt;
	if (m_fAnimationDt >= m_fAnimationSpeed)
	{
		m_fAnimationDt = 0.0f;
		ShEntity2::SetShow(m_aAttackAnimation[m_eCurrentAnimationType][m_currentSprite++], false);

		if (m_currentSprite >= m_aAttackAnimation[m_eCurrentAnimationType].GetCount())
		{ // Animation ended
			m_currentSprite = 0;

			if (m_bIsAttacking)
			{
				m_pCurrentTarget->TakeSlowEffect(0.5f);

				m_bIsAttacking = false;
				m_fAttackCooldown = m_fAttackSpeed;
				m_eCurrentAnimationType = animation_idle;
			}
		}

		ShEntity2::SetShow(m_aAttackAnimation[m_eCurrentAnimationType][m_currentSprite], true);
	}

	TowerBase::Update(dt);
}

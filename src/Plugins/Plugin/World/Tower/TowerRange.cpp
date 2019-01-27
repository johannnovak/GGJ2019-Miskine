#include "TowerRange.h"
#include "TowerBase.h"
#include "TowerProjectile.h"

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
void TowerRange::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_eTowerAttackType = tower_range;

	m_fRadiusMin = 150.0f;
	m_fRadiusMax = 300.0f;

	TowerBase::Initialize(levelIdentifier, pEnemyManager, towerType, focusType, position, damages, attackSpeed, rangeAOE);	

	char szSpriteIdentifier[1024];
			
	switch (towerType)
	{
		case tower_fils: sprintf(szSpriteIdentifier, "fils"); break;
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
void TowerRange::Release(void)
{
	int nProjectileCount = m_aProjectile.GetCount();
	for (int i = 0; i < nProjectileCount; ++i)
	{
		m_aProjectile[i].Release();
	}
	m_aProjectile.Empty();

	TowerBase::Release();
}

/**
 * @brief Update
 */
void TowerRange::Update(float dt)
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
				// Create + launch projectile
				ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("game"), CShIdentifier("fils_projectile"), CShVector3(m_vPosition, 11.0f), CShEulerAngles::ZERO, CShVector3(0.4f, 0.4f, 1.0f));
				SH_ASSERT(shNULL != pEntity);

				TowerProjectile projectile;
				projectile.Initialize(m_vPosition, 20.0f, m_pCurrentTarget, pEntity);
				m_aProjectile.Add(projectile);

				m_bIsAttacking = false;
				m_fAttackCooldown = m_fAttackSpeed;
				m_eCurrentAnimationType = animation_idle;
			}
		}

		ShEntity2::SetShow(m_aAttackAnimation[m_eCurrentAnimationType][m_currentSprite], true);
	}

	// Update projectiles
	for (int i = 0; i < m_aProjectile.GetCount(); ++i)
	{
		if (m_aProjectile[i].Update(dt))
		{ // Target hited

			Enemy * pTarget = m_aProjectile[i].GetTarget();
			pTarget->TakeDamages(m_damages);

			if (-1 != m_fAOERange)
			{ 
				const CShVector2 & targetPos = m_aProjectile[i].GetPosition();

				CShArray<Enemy*> aEnemyList;
				m_pEnemyManager->GetEnemyListInRange(aEnemyList, targetPos, 0.0f, m_fAOERange);

				int nEnemyCount = aEnemyList.GetCount();
				for (int i = 0; i < nEnemyCount; ++i)
				{
					// Damages / 2
					aEnemyList[i]->TakeDamages(m_damages * 0.5f);
				}
			}

			if (pTarget->IsDead())
			{
				if (pTarget == m_pCurrentTarget)
				{
					m_pCurrentTarget = shNULL;
				}
				m_aProjectile.Remove(i--);
			}
		}
	}

	TowerBase::Update(dt);
}

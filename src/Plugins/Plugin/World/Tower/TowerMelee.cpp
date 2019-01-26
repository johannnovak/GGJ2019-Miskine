#include "TowerMelee.h"
#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy/EnemyManager.h"
#include "../Enemy/Enemy.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerMelee::TowerMelee(void)
: TowerBase()
{

}

/**
 * @brief Destructor
 */
TowerMelee::~TowerMelee(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerMelee::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_eTowerAttackType = tower_melee;

	m_fRadiusMin = 10.0f;
	m_fRadiusMax = 200.0f;

	TowerBase::Initialize(levelIdentifier, pEnemyManager, towerType, focusType, position, damages, attackSpeed, rangeAOE);

	//ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("player"), CShIdentifier("walk_01"), m_vPosition, CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
	//SH_ASSERT(shNULL != pEntity);
	//m_aAttackAnimation.Add(pEntity);

	char szSpriteIdentifier[1024];
			
	switch (towerType)
	{
		case tower_pere : sprintf(szSpriteIdentifier, "pere"); break;
		case tower_mere: sprintf(szSpriteIdentifier, "mere"); break;
		default: sprintf(szSpriteIdentifier, "pere"); break;
	}

	char szDirection[32];

	for (int i = 0; i < direction_max; ++i)
	{
		switch ((EAnimationType)i)
		{
			case animation_top:sprintf(szDirection, "attack_back");
			case animation_bottom:sprintf(szDirection, "attack_front");
			case animation_left:sprintf(szDirection, "attack_left");
			case animation_right:sprintf(szDirection, "attack_right");
			case animation_idle:sprintf(szDirection, "idle");
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
			ShEntity2 * pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), pSprite, CShVector3(0.0f, 0.0f, 1.0f), CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f), false);
			aEntityList.Add(pEntity);
		}
		m_aAttackAnimation[i] = aEntityList;
	}
}

/**
 * @brief Release
 */
void TowerMelee::Release(void)
{

}

/**
 * @brief Update
 */
void TowerMelee::Update(float dt)
{
	if (m_bIsAttacking)
	{
		m_fAnimationDt += dt;
		if (m_fAnimationDt >= m_fAnimationSpeed)
		{
			m_fAnimationDt = 0.0f;
			// TODO Animate

			// TODO if animation ended
			{ // Attack ended
				if (m_pCurrentTarget->IsDead())
				{
					m_pCurrentTarget = shNULL;
				}
				else
				{
					m_pCurrentTarget->TakeDamages(m_damages);
					if (m_pCurrentTarget->IsDead())
					{
						m_pCurrentTarget = shNULL;
					}

					if (-1 != m_fAOERange)
					{ // Hit enemies in currentTarget range
						const CShVector3 & targetPos = m_pCurrentTarget->GetPosition();

						CShArray<Enemy*> aEnemyList;
						m_pEnemyManager->GetEnemyListInRange(aEnemyList, targetPos, 0.0f, m_fAOERange);

						int nEnemyCount = aEnemyList.GetCount();
						for (int i = 0; i < nEnemyCount; ++i)
						{
							// Damages / 2
							aEnemyList[i]->TakeDamages(m_damages * 0.5f);
						}
					}
				}

				m_bIsAttacking = false;
				m_fAttackCooldown = 0.0f;
			}
		}
	}
	else
	{
		m_fAttackCooldown += dt;

		if (m_fAttackCooldown >= m_fAttackSpeed)
		{
			if (m_pCurrentTarget)
			{
				const CShVector3 & targetPos = m_pCurrentTarget->GetPosition();

				float distSquared = Plugin::GetDistanceSquared(m_vPosition, targetPos);
				if (distSquared > m_fRadiusMax * m_fRadiusMax
					|| distSquared < m_fRadiusMin * m_fRadiusMin)
				{// Lost focus
					SH_TRACE("FOCUS LOST\n");
					m_pCurrentTarget = shNULL;
				}
			}

			if (shNULL == m_pCurrentTarget)
			{
				// Find potential enemy based on focus type
				CShArray<Enemy *> aEnemyList;
				m_pEnemyManager->GetEnemyListInRange(aEnemyList, m_vPosition, m_fRadiusMin, m_fRadiusMax);

				int currentId = -1;
				int health = -1;
				float distSquared = m_fRadiusMax * m_fRadiusMax;
				int nEnemyCount = aEnemyList.GetCount();
				for (int i = 0; i < nEnemyCount; ++i)
				{
					Enemy * pEnemy = aEnemyList[i];

					switch (m_eFocusType)
					{
					case focus_nearest:
					{
						const CShVector3 & enemyPos = pEnemy->GetPosition();
						float dist = Plugin::GetDistanceSquared(m_vPosition, enemyPos);

						if (dist < distSquared)
						{
							currentId = i;
							distSquared = dist;
						}
					}
					break;

					case focus_biggest_lifebase:
					{
						int enemyHealth = pEnemy->GetBaseHealth();
						if (enemyHealth > health)
						{
							currentId = i;
							health = enemyHealth;
						}
					}
					break;

					case focus_lowest_life:
					{
						int enemyHealth = pEnemy->GetCurrentHealth();
						if (enemyHealth == -1 || enemyHealth < health)
						{
							currentId = i;
							health = enemyHealth;
						}
					}
					break;
					}
				}

				if (-1 != currentId)
				{
					m_pCurrentTarget = aEnemyList[currentId];
					SH_TRACE("FOCUS TARGET\n");
				}
			}

			if (m_pCurrentTarget)
			{
				// Shoot target
				m_bIsAttacking = true;
				SH_TRACE("ATTACK TARGET\n");
			}
		}
	}
}

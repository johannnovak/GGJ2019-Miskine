#include "TowerBase.h"

#include "ShSDK/ShSDK.h"

#include "../Enemy/EnemyManager.h"
#include "../Enemy/Enemy.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
TowerBase::TowerBase(void)
: m_eTowerType(tower_pere)
, m_eTowerAttackType(tower_melee)
, m_eFocusType(focus_nearest)
, m_vPosition(CShVector2::ZERO)
, m_fRadiusMin(0.0f)
, m_fRadiusMax(100.0f)
, m_pDebugRadiusMin(shNULL)
, m_pDebugRadiusMax(shNULL)
, m_damages(0)
, m_bIsAttacking(false)
, m_fAttackCooldown(0.0f)
, m_fAttackSpeed(0.0f)
, m_level(0)
, m_pEnemyManager(shNULL)
, m_pCurrentTarget(shNULL)
, m_fAOERange(-1.0f)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.4f)
, m_currentSprite(0)
, m_eCurrentAnimationType(animation_idle)
, m_aAttackAnimation()
{

}

/**
 * @brief Destructor
 */
TowerBase::~TowerBase(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerBase::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE /*= -1.0f*/)
{
	m_levelIdentifier = levelIdentifier;

	m_eTowerType = towerType;
	m_eFocusType = focusType;
	m_vPosition = position;
	m_damages = damages;
	m_fAttackSpeed = attackSpeed;

	m_pEnemyManager = pEnemyManager;
	SH_ASSERT(shNULL != m_pEnemyManager);
	
	m_fAOERange = rangeAOE;

	m_pDebugRadiusMin = ShPrimitiveCircle::Create(m_levelIdentifier, CShIdentifier("rangeMin"), CShVector3(m_vPosition,0.0f), m_fRadiusMin, 8, CShRGBAf_RED);
	SH_ASSERT(shNULL != m_pDebugRadiusMin);
	ShPrimitiveCircle::Set2d(m_pDebugRadiusMin, true);
	m_pDebugRadiusMax = ShPrimitiveCircle::Create(m_levelIdentifier, CShIdentifier("rangeMax"), CShVector3(m_vPosition, 0.0f), m_fRadiusMax, 8, CShRGBAf_RED);
	SH_ASSERT(shNULL != m_pDebugRadiusMax);
	ShPrimitiveCircle::Set2d(m_pDebugRadiusMax, true);
}

/**
 * @brief Release
 */
void TowerBase::Release(void)
{
	ShPrimitiveCircle::Destroy(m_pDebugRadiusMin);
	ShPrimitiveCircle::Destroy(m_pDebugRadiusMax);

	for (int i = 0; i < animation_max; ++i)
	{
		int nAttackAnimCount = m_aAttackAnimation[i].GetCount();
		for (int j = 0; j < nAttackAnimCount; ++j)
		{
			ShEntity2::Destroy(m_aAttackAnimation[i][j]);
		}
		m_aAttackAnimation[i].Empty();
	}
}

/**
 * @brief Update
 */
void TowerBase::Update(float dt)
{
	// Search for target
	if (!m_bIsAttacking)
	{
		m_fAttackCooldown += dt;

		if (m_fAttackCooldown >= m_fAttackSpeed)
		{
			if (m_pCurrentTarget)
			{
				const CShVector2 & targetPos = m_pCurrentTarget->GetPosition();

				float distSquared = Plugin::GetDistanceSquared(m_vPosition, targetPos);
				if (distSquared > m_fRadiusMax * m_fRadiusMax
					|| distSquared < m_fRadiusMin * m_fRadiusMin)
				{// Lost focus
					if (!m_bIsAttacking)
					{
						m_pCurrentTarget = shNULL;
					}
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
						const CShVector2 & enemyPos = pEnemy->GetPosition();
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
				}
			}
		}

		if (m_pCurrentTarget)
		{
			// Attack target
			m_bIsAttacking = true;

			const CShVector2 & targetPos = m_pCurrentTarget->GetPosition();

			float theta = shAtan2f(targetPos.m_y - m_vPosition.m_y, targetPos.m_x - m_vPosition.m_x);
			theta += SHC_PI / 2.0f;
			float angle = theta * SHC_RAD2DEG;

			if (angle < 0) 
			{
				angle += 360;
			}

			EAnimationType eCurrentAnim = m_eCurrentAnimationType;

			if (angle > 315.0f || angle <= 45.0f)
			{ // Bottom
				eCurrentAnim = animation_bottom;
			}
			else if (angle > 45.0f && angle <= 135)
			{ // Right
				eCurrentAnim = animation_right;
			}
			else if (angle > 135 && angle <= 225)
			{ // Top
				eCurrentAnim = animation_top;
			}
			else
			{ // Left
				eCurrentAnim = animation_left;
			}

			if (eCurrentAnim != m_eCurrentAnimationType)
			{				
				ShEntity2::SetShow(m_aAttackAnimation[m_eCurrentAnimationType][m_currentSprite], false);
				m_eCurrentAnimationType = eCurrentAnim;
				m_currentSprite = 0;
				ShEntity2::SetShow(m_aAttackAnimation[m_eCurrentAnimationType][m_currentSprite], true);
			}
		}
	}
}

/**
 * @brief LevelUp
 */
void TowerBase::LevelUp(void)
{
	m_level++;
	m_damages += 10;
	m_fAttackSpeed -= 1.0f;
	// Ranges ?
}

/**
 * @brief GetCurrentLevel
 */
int TowerBase::GetCurrentLevel(void)
{
	return m_level;
}

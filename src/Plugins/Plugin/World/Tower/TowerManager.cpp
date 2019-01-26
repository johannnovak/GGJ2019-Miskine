#include "TowerManager.h"

#include "../Enemy/EnemyManager.h"

/**
 * @brief Constructor
 */
TowerManager::TowerManager(void)
: m_pEnemyManager(shNULL)
, m_aTowerList()
{
	// ...
}

/**
 * @brief Destructor
 */
TowerManager::~TowerManager(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void TowerManager::Initialize(EnemyManager * pEnemyManager)
{
	m_pEnemyManager = pEnemyManager;
	SH_ASSERT(shNULL != m_pEnemyManager);
}

/**
 * @brief Release
 */
void TowerManager::Release(void)
{
	int nTowerCount = m_aTowerList.GetCount();
	for (int i = 0; i < nTowerCount; ++i)
	{
		m_aTowerList[i].Release();
	}
	m_aTowerList.Empty();
}

/**
 * @brief Update
 */
void TowerManager::Update(float dt)
{
	int nTowerCount = m_aTowerList.GetCount();
	for (int i = 0; i < nTowerCount; ++i)
	{
		m_aTowerList[i].Update(dt);
	}
}

/**
 * @brief CreateTower
 */
void TowerManager::CreateTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector3 & position, float damages, float attackSpeed)
{
	TowerBase tower;
	tower.Initialize(m_pEnemyManager, towerType, focusType, position, damages, attackSpeed);
	m_aTowerList.Add(tower);
}

/**
 * @brief GetTowerList
 */
void TowerManager::GetTowerList(CShArray<TowerBase*>& aTowerList)
{
	int nTowerCount = aTowerList.GetCount();
	for (int i = 0; i < nTowerCount; ++i)
	{
		aTowerList.Add(&m_aTowerList[i]);
	}
}

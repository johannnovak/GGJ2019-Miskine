#include "TowerManager.h"
#include "TowerMelee.h"
#include "TowerRange.h"

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
void TowerManager::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager)
{
	m_levelIdentifier = levelIdentifier;

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
		m_aTowerList[i]->Release();
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
		m_aTowerList[i]->Update(dt);
	}
}

/**
 * @brief CreateTower
 */
void TowerManager::CreateTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed)
{
	switch (towerType)
	{
	case TowerBase::tower_pere: CreateMeleeTower(towerType, focusType, position, damages, attackSpeed); break;
	case TowerBase::tower_mere: CreateMeleeTower(towerType, focusType, position, damages, attackSpeed); break;
	case TowerBase::tower_fille: CreateRangeTower(towerType, focusType, position, damages, attackSpeed); break;
	case TowerBase::tower_fils: CreateRangeTower(towerType, focusType, position, damages, attackSpeed); break;

	}
}

/**
 * @brief CreateMeleeTower
 */
void TowerManager::CreateMeleeTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed)
{
	TowerMelee * pTower = new TowerMelee();
	pTower->Initialize(m_levelIdentifier, m_pEnemyManager, towerType, focusType, position, damages, attackSpeed);
	m_aTowerList.Add(pTower);
}

/**
 * @brief CreateRangeTower
 */
void TowerManager::CreateRangeTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed)
{
	TowerRange * pTower = new TowerRange();
	pTower->Initialize(m_levelIdentifier, m_pEnemyManager, towerType, focusType, position, damages, attackSpeed);
	m_aTowerList.Add(pTower);
}

/**
 * @brief GetTowerList
 */
void TowerManager::GetTowerList(CShArray<TowerBase*>& aTowerList)
{
	int nTowerCount = aTowerList.GetCount();
	for (int i = 0; i < nTowerCount; ++i)
	{
		aTowerList.Add(m_aTowerList[i]);
	}
}

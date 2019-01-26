#include "TowerManager.h"

#include "../Wave/WaveManager.h"

/**
 * @brief Constructor
 */
TowerManager::TowerManager(void)
: m_pWaveManager(shNULL)
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
void TowerManager::Initialize(const CShIdentifier & levelIdentifier, WaveManager * pWaveManager)
{
	m_levelIdentifier = levelIdentifier;

	m_pWaveManager = pWaveManager;
	SH_ASSERT(shNULL != m_pWaveManager);
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
void TowerManager::CreateTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed)
{
	TowerBase tower;
	tower.Initialize(m_levelIdentifier, m_pWaveManager, towerType, focusType, position, damages, attackSpeed);
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

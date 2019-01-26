#include "TowerManager.h"

#include "TowerBase.h"

/**
 * @brief Constructor
 */
TowerManager::TowerManager(void)
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
void TowerManager::Initialize()
{
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
		SH_SAFE_FREE(m_aTowerList[i]);
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
void TowerManager::CreateTower(void)
{
	int nTowerCount = m_aTowerList.GetCount();
	for (int i = 0; i < nTowerCount; ++i)
	{
		TowerBase * pTower = new TowerBase();
		//todo pTower->Initialize();
		m_aTowerList.Add(pTower);
	}
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

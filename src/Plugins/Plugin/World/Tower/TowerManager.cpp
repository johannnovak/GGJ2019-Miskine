#include "TowerManager.h"
#include "TowerMelee.h"
#include "TowerRange.h"
#include "TowerSupport.h"

#include "../Enemy/EnemyManager.h"

#include "../../Plugin.h"
#include "../../PluginFactory.h"

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
TowerBase * TowerManager::CreateTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed)
{
	int iMoneyToLoose = GetCostByType(towerType);

	switch (towerType)
	{
		case TowerBase::tower_pere:		
		{	
			CreateMeleeTower(towerType, focusType, position, damages, attackSpeed);
		} 
		break;

		case TowerBase::tower_mere:		
		{	
			CreateMeleeTower(towerType, focusType, position, damages, attackSpeed);
		} 
		break;

		case TowerBase::tower_fille:	
		{	
			CreateSupportTower(towerType, focusType, position, damages, attackSpeed);
		} 
		break;

		case TowerBase::tower_fils:		
		{	
			CreateRangeTower(towerType, focusType, position, damages, attackSpeed);
		} 
		break;
	}

	static_cast<Plugin*>(GetPlugin())->GetWorld().LooseMoney(iMoneyToLoose);

	return m_aTowerList[m_aTowerList.GetCount()-1];
}

/**
 * @brief DeleteTower
 */
void TowerManager::DeleteTower(TowerBase * pTower)
{
	int iFindIndex = m_aTowerList.Find(pTower);
	if (-1 != iFindIndex)
	{
		m_aTowerList.Remove(iFindIndex);
	}
}
	
/**
 * @brief SellTower
 */
int TowerManager::SellTower(TowerBase * pTowerToSell)
{
	if (shNULL != pTowerToSell)
	{
		int iMoneyToGain = 0;
		int iCost = 0;
		switch (pTowerToSell->GetType())
		{
			case TowerBase::tower_pere:		
			{	
				iCost = TOWER_PERE_COST_DIFFICULTY_MEDIUM;
			} 
			break;

			case TowerBase::tower_mere:		
			{	
				iCost = TOWER_MERE_COST_DIFFICULTY_MEDIUM;
			} 
			break;

			case TowerBase::tower_fille:	
			{	
				iCost = TOWER_FILLE_COST_DIFFICULTY_MEDIUM;
			} 
			break;

			case TowerBase::tower_fils:		
			{	
				iCost = TOWER_FILS_COST_DIFFICULTY_MEDIUM;
			} 
			break;
		}

		iMoneyToGain = static_cast<int>(iCost * (1.0f + 0.5f * pTowerToSell->GetLevel())  / 2.0f);
		static_cast<Plugin*>(GetPlugin())->GetWorld().GainMoney(iMoneyToGain);

		DeleteTower(pTowerToSell);
	}

	return 0;
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
 * @brief CreateSupportTower
 */
void TowerManager::CreateSupportTower(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed)
{
	TowerSupport * pTower = new TowerSupport();
	pTower->Initialize(m_levelIdentifier, m_pEnemyManager, towerType, focusType, position, damages, attackSpeed);
	m_aTowerList.Add(pTower);
}

/**
 * @brief GetTowerList
 */
void TowerManager::GetTowerList(CShArray<TowerBase*>& aTowerList)
{
	int nTowerCount = m_aTowerList.GetCount();
	for (int i = 0; i < nTowerCount; ++i)
	{
		aTowerList.Add(m_aTowerList[i]);
	}
}

/**
 * @brief TowerManager::GetCostByType
 * @param towerType
 * @return
 */
int TowerManager::GetCostByType(TowerBase::ETowerType towerType)
{
	switch (towerType)
	{
		case TowerBase::tower_pere:
		{
			return TOWER_PERE_COST_DIFFICULTY_MEDIUM;
		}
		break;

		case TowerBase::tower_mere:
		{
			return TOWER_MERE_COST_DIFFICULTY_MEDIUM;
		}
		break;

		case TowerBase::tower_fille:
		{
			return TOWER_FILLE_COST_DIFFICULTY_MEDIUM;
		}
		break;

		case TowerBase::tower_fils:
		{
			return TOWER_FILS_COST_DIFFICULTY_MEDIUM;
		}
		break;
	}

	return 0;
}

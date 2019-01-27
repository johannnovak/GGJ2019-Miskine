#pragma once

#include "ShSDK/ShSDK.h"

#include "TowerBase.h"

#define TOWER_PERE_COST_DIFFICULTY_LOW 500
#define TOWER_PERE_COST_DIFFICULTY_MEDIUM 600
#define TOWER_PERE_COST_DIFFICULTY_HIGH 700

#define TOWER_MERE_COST_DIFFICULTY_LOW 400
#define TOWER_MERE_COST_DIFFICULTY_MEDIUM 500
#define TOWER_MERE_COST_DIFFICULTY_HIGH 600

#define TOWER_FILS_COST_DIFFICULTY_LOW 700
#define TOWER_FILS_COST_DIFFICULTY_MEDIUM 800
#define TOWER_FILS_COST_DIFFICULTY_HIGH 1000

#define TOWER_FILLE_COST_DIFFICULTY_LOW 300
#define TOWER_FILLE_COST_DIFFICULTY_MEDIUM 400
#define TOWER_FILLE_COST_DIFFICULTY_HIGH 500

class EnemyManager;

class TowerManager
{
public:
	explicit	 TowerManager		(void);
	virtual		~TowerManager		(void);

	void		Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager);
	void		Release				(void);

	void		Update				(float dt);

	void		CreateTower			(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed);
	void		DeleteTower			(TowerBase * pTower);
	int 		SellTower			(TowerBase * pTowerToSell);

	void		GetTowerList		(CShArray<TowerBase *>& aTowerList);

private:
	void		CreateMeleeTower	(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed);
	void		CreateRangeTower	(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed);
	void		CreateSupportTower	(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed);

private:
	CShIdentifier			m_levelIdentifier;

	EnemyManager *			m_pEnemyManager;

	CShArray<TowerBase *>		m_aTowerList;
};


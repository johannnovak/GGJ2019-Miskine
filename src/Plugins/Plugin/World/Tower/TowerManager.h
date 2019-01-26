#pragma once

#include "ShSDK/ShSDK.h"

#include "TowerBase.h"

class EnemyManager;

class TowerManager
{
public:

	explicit	 TowerManager	(void);
	virtual		~TowerManager	(void);

	void		Initialize		(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager);
	void		Release			(void);

	void		Update			(float dt);

	void		CreateTower		(TowerBase::ETowerType towerType, TowerBase::EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed);

	void		GetTowerList	(CShArray<TowerBase *>& aTowerList);

private:
	
	CShIdentifier			m_levelIdentifier;

	EnemyManager *			m_pEnemyManager;

	CShArray<TowerBase>		m_aTowerList;
};


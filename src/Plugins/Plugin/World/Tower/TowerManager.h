#pragma once

#include "ShSDK/ShSDK.h"

class TowerBase;

class TowerManager
{
public:

	explicit	 TowerManager	(void);
	virtual		~TowerManager	(void);

	void		Initialize		(void);
	void		Release			(void);

	void		Update			(float dt);

	void		CreateTower		(void);

	void		GetTowerList	(CShArray<TowerBase *>& aTowerList);

private:

	CShArray<TowerBase *>	m_aTowerList;
};


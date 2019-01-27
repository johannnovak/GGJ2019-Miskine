#pragma once

class TowerBase;

class IWorldListener
{
public:
	virtual void OnTowerCreated		(TowerBase * pTower) = 0;

	virtual void OnMoneyUpdated		(int iMoneyAmount) = 0;
	
	virtual void OnHPUpdated		(int iHPAmount) = 0;
};


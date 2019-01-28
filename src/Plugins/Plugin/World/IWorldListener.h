#pragma once

class TowerBase;

class IWorldListener
{
public:
	virtual void OnTowerCreated			(TowerBase * pTower) = 0;
	virtual void OnTowerSelected		(TowerBase * pTower) = 0;
	virtual void OnTowerUnselected		(TowerBase * pTower) = 0;
	virtual void OnTowerUpgraded		(TowerBase * pTower) = 0;
	virtual void OnTowerSold			(TowerBase * pTower) = 0;

	virtual void OnMoneyUpdated			(int iMoneyAmount) = 0;
	
	virtual void OnHPUpdated			(int iHPAmount) = 0;

	virtual void OnWaveUpdated			(int iWave) = 0;
};


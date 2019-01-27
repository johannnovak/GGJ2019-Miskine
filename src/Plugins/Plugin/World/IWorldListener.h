#pragma once

class IWorldListener
{
public:
	virtual void OnTowerCreated		(void) = 0;

	virtual void OnMoneyUpdated		(int iMoneyAmount) = 0;
	
	virtual void OnHPUpdated		(int iHPAmount) = 0;
};

#pragma once

#include "ShSDK/ShSDK.h"

#include "TowerBase.h"

class TowerMelee : public TowerBase
{
public:

	explicit	 TowerMelee			(void);
	virtual		~TowerMelee			(void);

	void		Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed, float rangeAOE = -1.0f);
	void		Release				(void);

	void		Update				(float dt);

};

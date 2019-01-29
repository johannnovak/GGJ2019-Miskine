#pragma once

#include "ShSDK/ShSDK.h"

#include "TowerBase.h"

class TowerMelee : public TowerBase
{
public:

	explicit	 TowerMelee					(void);
	virtual		~TowerMelee					(void);

	virtual void	Initialize				(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE = -1.0f) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update					(float dt) SH_ATTRIBUTE_OVERRIDE;
};

#pragma once

#include "TowerBase.h"

class TowerSupport : public TowerBase
{
public:

	explicit		TowerSupport		(void);
	virtual			~TowerSupport		(void);

	virtual void	Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE = -1.0f) SH_ATTRIBUTE_OVERRIDE;
	virtual void	Release				(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

};

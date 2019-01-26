#pragma once

#include "ShSDK/ShSDK.h"

#include "TowerBase.h"

class TowerRange : public TowerBase
{
public:

	explicit		TowerRange			(void);
	virtual			~TowerRange			(void);

	virtual void	Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, TowerBase::ETowerType towerType, EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed, float rangeAOE = -1.0f) SH_ATTRIBUTE_OVERRIDE;
	virtual void	Release				(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

private:
	
	ShEntity2 *	m_pProjectile;

};

#pragma once

#include "ShSDK/ShSDK.h"

class enemy;

class TowerBase
{
public:

	enum ETowerType
	{
		tower_melee,
		tower_range
	};

	enum EFocusType
	{
		focus_nearest,
		focus_most_life,
		focus_biggest_lifebase,
	};

	explicit	 TowerBase		(ETowerType towerType, EFocusType focusType, float damage, float attackSpeed);
	virtual		~TowerBase		(void);

	void		Initialize		(void);
	void		Release			(void);

	void		Update			(float dt);

protected:
	
	ETowerType				m_eTowerType;
	EFocusType				m_eFocusType;

	float					m_fRadiusMin;
	float					m_fRadiusMax;

	float					m_fDamage;

	bool					m_bIsAttacking;
	float					m_fAttackCooldown;
	float					m_fAttackSpeed;

	int						m_level;

	enemy *					m_pCurrentTarget;

	CShArray<ShEntity2 *>	m_aAttackAnimation;

	//Évolutions possibles	
};


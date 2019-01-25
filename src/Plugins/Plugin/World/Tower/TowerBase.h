#pragma once

#include "ShSDK/ShSDK.h"

class Enemy;

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

	explicit	 TowerBase		(void);
	virtual		~TowerBase		(void);

	void		Initialize		(ETowerType towerType, EFocusType focusType, float damages, float attackSpeed);
	void		Release			(void);

	void		Update			(float dt);

protected:
	
	ETowerType				m_eTowerType;
	EFocusType				m_eFocusType;

	float					m_fRadiusMin;
	float					m_fRadiusMax;

	float					m_fDamages;

	bool					m_bIsAttacking;
	float					m_fAttackCooldown;
	float					m_fAttackSpeed;

	int						m_level;

	Enemy *					m_pCurrentTarget;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	CShArray<ShEntity2 *>	m_aAttackAnimation;

	//Évolutions possibles	
};


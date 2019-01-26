#pragma once

#include "ShSDK/ShSDK.h"

class EnemyManager;
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
		focus_lowest_life,
		focus_biggest_lifebase,
	};

	explicit	 TowerBase			(void);
	virtual		~TowerBase			(void);

	void		Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, ETowerType towerType, EFocusType focusType, const CShVector3 & position, float damages, float attackSpeed, float rangeAOE = -1.0f);
	void		Release				(void);

	void		Update				(float dt);

protected:

	CShIdentifier			m_levelIdentifier;

	ETowerType				m_eTowerType;
	EFocusType				m_eFocusType;

	CShVector3				m_vPosition;

	float					m_fRadiusMin;
	float					m_fRadiusMax;

	float					m_fDamages;

	bool					m_bIsAttacking;
	float					m_fAttackCooldown;
	float					m_fAttackSpeed;

	int						m_level;

	EnemyManager *			m_pEnemyManager;
	Enemy *					m_pCurrentTarget;

	float					m_fAOERange;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	CShArray<ShEntity2 *>	m_aAttackAnimation;

	//Évolutions possibles	
};


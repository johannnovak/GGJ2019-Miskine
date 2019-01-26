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

	explicit		TowerBase			(void);
	virtual			~TowerBase			(void);

	virtual void	Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, EFocusType focusType, const CShVector3 & position, int damages, float attackSpeed, float rangeAOE = -1.0f);
	virtual void	Release				(void);

	virtual void	Update				(float dt);

	void			LevelUp				(void);

	int				GetCurrentLevel		(void);

protected:

	CShIdentifier			m_levelIdentifier;

	ETowerType				m_eTowerType;
	EFocusType				m_eFocusType;

	CShVector3				m_vPosition;

	float					m_fRadiusMin;
	float					m_fRadiusMax;

	ShPrimitiveCircle *		m_pDebugRadiusMin;
	ShPrimitiveCircle *		m_pDebugRadiusMax;

	int						m_damages;

	bool					m_bIsAttacking;
	float					m_fAttackCooldown;
	float					m_fAttackSpeed;

	int						m_level;

	EnemyManager *			m_pEnemyManager;
	Enemy *					m_pCurrentTarget;

	float					m_fAOERange;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	int						m_currentSprite;
	CShArray<ShEntity2 *>	m_aAttackAnimation;

	//Évolutions possibles	
};


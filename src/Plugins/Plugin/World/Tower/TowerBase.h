#pragma once

#include "ShSDK/ShSDK.h"

class EnemyManager;
class Enemy;

class TowerBase
{
public:

	enum EAnimationType
	{
		animation_top,
		animation_bottom,
		animation_left,
		animation_right,
		animation_idle,

		animation_max
	};

	enum ETowerType
	{
		tower_pere,
		tower_mere,
		tower_fille,
		tower_fils
	};

	enum ETowerAttackType
	{
		tower_melee,
		tower_range,
		tower_support
	};

	enum EFocusType
	{
		focus_nearest,
		focus_lowest_life,
		focus_biggest_lifebase,
	};

	explicit			TowerBase					(void);
	virtual				~TowerBase					(void);

	virtual void		Initialize					(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, ETowerType towerType, EFocusType focusType, const CShVector2 & position, int damages, float attackSpeed, float rangeAOE = -1.0f);
	virtual void		Release						(void);

	virtual void		Update						(float dt);

	void				LevelUp						(void);

	int					GetCurrentLevel				(void);
	ETowerType			GetType						(void);
	int					GetLevel					(void);
	int					GetNeededMoneyToUpgrade		(void);

	const CShVector2 &	GetPosition					(void) const
	{
		return m_vPosition;
	}

	ShEntity2 *			GetCurrentEntity2			(void);

protected:

	CShIdentifier			m_levelIdentifier;

	ETowerType				m_eTowerType;
	ETowerAttackType		m_eTowerAttackType;
	EFocusType				m_eFocusType;

	CShVector2				m_vPosition;

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
	EAnimationType			m_eCurrentAnimationType;
	CShArray<ShEntity2 *>	m_aAttackAnimation[animation_max];
};


#pragma once

#include "ShSDK/ShSDK.h"

class Enemy
{
	enum EState
	{
		e_state_on,
		e_state_off
	};

public:

	explicit	 Enemy				(void);
	virtual		~Enemy				(void);

	void		Initialize			(ShEntity2* pEntity, int iBaseHealth);
	void		Release				(void);

	void		Start				(const CShVector3 & vPosition);
	void		Stop				(void);

	void		Update				(float dt);

	void		TakeDamages			(float damages);

	const CShVector3 & GetPosition	(void) const;
	const int & GetBaseHealth		(void) const;
	const int & GetCurrentHealth	(void) const;

private:
	void		SetState			(EState state);

public:

private:
	EState					m_eState;
	float					m_fStateTime;

	ShEntity2 *				m_pEntity;
	ShEntity2 *				m_pEntityLifeBar;

	CShVector3				m_vPosition;

	int						m_baseHealth;
	int						m_currentHealth;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	CShArray<ShEntity2 *>	m_aMoveAnimation;
};


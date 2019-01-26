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

	explicit			 Enemy				(void);
	virtual				~Enemy				(void);

	void				Initialize			(const CShArray<ShEntity2*> aEntity, int iBaseHealth);
	void				Release				(void);

	void				Start				(const CShVector3 & vPosition);
	void				Stop				(void);

	void				Update				(float dt);

	void				TakeDamages			(int damages);

	const CShVector3 &	GetPosition			(void) const;
	const int &			GetBaseHealth		(void) const;
	const int &			GetCurrentHealth	(void) const;

	bool				IsDead				(void);

private:
	void				SetState			(EState state);

private:
	EState					m_eState;
	float					m_fStateTime;

	ShEntity2 *				m_pEntityLifeBar;

	CShVector3				m_vPosition;

	int						m_baseHealth;
	int						m_currentHealth;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	int						m_currentSprite;
	CShArray<ShEntity2 *>	m_aMoveAnimation;
};


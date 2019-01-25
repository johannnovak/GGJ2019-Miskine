#pragma once

#include "ShSDK/ShSDK.h"

class Enemy
{
public:

	explicit	 Enemy				(void);
	virtual		~Enemy				(void);

	void		Initialize			(const CShIdentifier & levelIdentifier, const CShIdentifier & spriteIdentifier, const CShVector3 & position, int health);
	void		Release				(void);

	void		Update				(float dt);

	void		TakeDamages			(float damages);

	const CShVector3 & GetPosition	(void);

private:

	ShEntity2 *				m_pEntity;

	CShVector3				m_vPosition;

	int						m_health;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	CShArray<ShEntity2 *>	m_aMoveAnimation;

};


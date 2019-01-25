#pragma once

#include "ShSDK/ShSDK.h"

class Enemy
{
public:

	explicit	 Enemy			(void);
	virtual		~Enemy			(void);

	void		Initialize		(const CShIdentifier & levelIdentifier, const CShIdentifier & spriteIdentifier, int health);
	void		Release			(void);

	void		Update			(float dt);

	void		TakeDamages		(float damages);

private:

	int				m_health;

	ShEntity2 *		m_pEntity;
};


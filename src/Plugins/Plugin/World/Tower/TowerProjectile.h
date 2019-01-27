#pragma once

#include "ShSDK/ShSDK.h"

class Enemy;

class TowerProjectile
{
public:

	explicit	TowerProjectile			(void);
	virtual		~TowerProjectile		(void);

	void		Initialize				(const CShVector2 & pos, float speed, Enemy * pTarget, ShEntity2 * pEntity);
	void		Release					(void);

	bool		Update					(float dt);

	Enemy *		GetTarget				(void);

private:

	float		m_fSpeed;

	CShVector2	m_vPosition;
	Enemy *		m_pTarget;

	ShEntity2 * m_pEntity;
};


#pragma once

#include "ShSDK/ShSDK.h"

class Enemy;

class TowerProjectile
{
public:

	explicit			TowerProjectile			(void);
	virtual				~TowerProjectile		(void);
	
	void				Initialize				(const CShVector2 & pos, float speed, Enemy * pTarget, ShEntity2 * pEntity);
	void				Release					(void);

	bool				Update					(float dt);

	Enemy *				GetTarget				(void);
	const CShVector2 &	GetPosition				(void) const;

private:

	float		m_fSpeed;
	float		m_fCompletion;
	CShVector2	m_v;

	CShVector2	m_vStartPosition;
	CShVector2	m_vPosition;
	Enemy *		m_pTarget;

	ShEntity2 * m_pEntity;
};


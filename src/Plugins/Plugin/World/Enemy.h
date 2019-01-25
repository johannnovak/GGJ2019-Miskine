#pragma once

#include "ShSDK/ShSDK.h"

class Enemy
{
public:

	explicit	 Enemy			(void);
	virtual		~Enemy			(void);

	void		Initialize		(const CShIdentifier & levelIdentifier, const CShIdentifier & spriteIdentifier, ShPath * pPath);
	void		Release			(void);

	void		Update			(float dt);

private:

	ShEntity2 *		m_pEntity;

};


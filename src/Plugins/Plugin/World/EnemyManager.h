#pragma once

#include "ShSDK/ShSDK.h"

class Enemy;

class EnemyManager
{
public:

	explicit	 EnemyManager	(void);
	virtual		~EnemyManager	(void);

	void		Initialize		(void);
	void		Release			(void);

	void		Update			(float dt);

	void		CreateEnemies	(int number);

	void		GetEnemyList	(CShArray<Enemy *>& aEnemyList);

private:

	CShArray<Enemy *>	m_aEnemyList;
};


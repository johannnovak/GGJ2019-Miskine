#pragma once

#include "ShSDK/ShSDK.h"

class Enemy;

class EnemyManager
{
public:

	explicit	 EnemyManager	(void);
	virtual		~EnemyManager	(void);

	void		Initialize		(const CShIdentifier & levelIdentifier);
	void		Release			(void);

	void		Update			(float dt);

	void		CreateEnemies	(int number);

	void		GetEnemyList		(CShArray<Enemy *>& aEnemyList);
	void		GetEnemyListInRange	(CShArray<Enemy *>& aEnemyList, const CShVector3 & pos, float rangeMin, float rangeMax);

private:

	CShIdentifier		m_levelIdentifier;

	CShArray<Enemy>		m_aEnemyList;
};

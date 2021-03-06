#pragma once

#include "ShSDK/ShSDK.h"
#include "Enemy.h"

class Enemy;

#define POOL_SIZE 50

class EnemyManager
{
public:
	enum EEnemy
	{
		e_enemy_01,
		e_enemy_max
	};

	explicit	 EnemyManager		(void);
	virtual		~EnemyManager		(void);

	void		Initialize			(const CShIdentifier & levelIdentifier);
	void		Release				(void);

	void		Update				(float dt);

	Enemy *		SpawnEnemy			(EEnemy eEnemy, const CShVector2 & vPosition, const CShVector2 & vDestination, float fSpeed);

	void		GetEnemyList		(CShArray<Enemy *>& aEnemyList);
	void		GetEnemyListInRange	(CShArray<Enemy *>& aEnemyList, const CShVector2 & pos, float rangeMin, float rangeMax);

private:

	Enemy	m_aEnemy[e_enemy_max][POOL_SIZE];
	int		m_aiCurrentEnemy[e_enemy_max];

	CShArray<Enemy*>		m_apActiveEnemy;
};


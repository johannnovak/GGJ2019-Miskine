#pragma once

#include "ShSDK/ShSDK.h"
#include "../Enemy/EnemyManager.h"

class Wave
{

public:
	enum EState
	{
		e_state_on,
		e_state_off,
	};

	explicit	 Wave				(void);
	virtual		~Wave				(void);

	void		Initialize			(const CShIdentifier & levelIdentifier, int iEnemyCount, float fTime);
	void		Release				(void);

	void		Start				(void);
	void		Stop				(void);

	void		GetEnemyListInRange	(CShArray<Enemy *>& aEnemyList, const CShVector3 & pos, float rangeMin, float rangeMax);

	void		Update				(float dt);
private:

public:

private:
	EState		 m_eState;
	EnemyManager m_enemyManager;
	int			 m_iRemainingEnemy;
	float		 m_fApparitionTime;
	float		 m_fTime;
};


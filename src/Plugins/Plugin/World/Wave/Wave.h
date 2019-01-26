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

	void		Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, int iEnemyCount, float fTime);
	void		Release				(void);

	void		Start				(void);
	void		Stop				(void);

	void		Update				(float dt);
private:

public:

private:
	EState			m_eState;
	EnemyManager *	m_pEnemyManager;
	int				m_iRemainingEnemy;
	float			m_fApparitionTime;
	float			m_fTime;
};


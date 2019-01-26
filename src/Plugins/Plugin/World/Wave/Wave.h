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

	void		Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, const CShArray<CShVector2> & aStartPosition, const CShVector2 & vDestination, int iEnemyCount, float fTime);
	void		Release				(void);

	void		Start				(void);
	void		Stop				(void);

	void		Update				(float dt);
private:

public:

private:
	EState				m_eState;
	EnemyManager *		m_pEnemyManager;
	CShArray<Enemy*>	m_apRemainingActiveEnemy;

	CShVector2			m_vStartPosition;
	CShVector2			m_vDestination;

	int					m_iRemainingEnemy;
	float				m_fApparitionTime;
	float				m_fTime;
};


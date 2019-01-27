#pragma once

#include "ShSDK/ShSDK.h"

#include "Wave.h"

class WaveManager
{
public:
	enum EState
	{
		e_state_on,
		e_state_off,
	};

	explicit	 WaveManager		(void);
	virtual		~WaveManager		(void);

	void		Initialize			(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager);
	void		Release				(void);

	void		InitWave			(CShArray<CShVector2>aStartPosition, CShVector2 vEndPosition, int iEnemyCount, float fApparitionTime, float fStartTime);

	void		Start				(void);
	void		Stop				(void);

	void		AddNextWave			(void);

	void		Update				(float dt);
private:
	CShIdentifier		m_levelIdentifier;
	EnemyManager*		m_pEnemyManager;

	EState				m_eState;
	CShArray<Wave>		m_aWave;
	CShArray<Wave*>		m_apActiveWave;

	int					m_iCurrentWave;
	float				m_fTime;
};


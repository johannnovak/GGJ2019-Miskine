#pragma once

#include "ShSDK/ShSDK.h"

#include "Wave.h"

#define WAVE_MAX 10
#define TIME_BETWEEN_WAVE 10.0f

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

	void		Start				(void);
	void		Stop				(void);

	void		AddWave				(void);

	void		Update				(float dt);
private:
	EState				m_eState;
	CShArray<Wave>		m_aWave;
	CShArray<Wave*>		m_apActiveWave;
	int					m_iCurrentWave;
	float				m_fTimeBetweenWave;
	float				m_fTime;
};


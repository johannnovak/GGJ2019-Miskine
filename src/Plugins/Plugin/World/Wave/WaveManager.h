#pragma once

#include "ShSDK/ShSDK.h"

#include "Wave.h"

#define WAVE_MAX 10
#define TIME_BETWEEN_WAVE 15.0f

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

	void		Initialize			(const CShIdentifier & levelIdentifier);
	void		Release				(void);

	void		Start				(void);
	void		Stop				(void);

	void		GetEnemyListInRange	(CShArray<Enemy *>& aEnemyList, const CShVector3 & pos, float rangeMin, float rangeMax);

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


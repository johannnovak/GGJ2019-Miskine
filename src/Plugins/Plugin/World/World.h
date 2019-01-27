#pragma once

#include "InputManager.h"
#include "Wave/WaveManager.h"
#include "Enemy/EnemyManager.h"
#include "Tower/TowerManager.h"

#include "IWorldListener.h"

#define DEFAULT_HP_DIFFICULTY_LOW 20
#define DEFAULT_HP_DIFFICULTY_MEDIUM 15
#define DEFAULT_HP_DIFFICULTY_HIGH 10

#define DEFAULT_MONEY_DIFFICULTY_LOW 200
#define DEFAULT_MONEY_DIFFICULTY_MEDIUM 150
#define DEFAULT_MONEY_DIFFICULTY_HIGH 100

class World
{
public:

	explicit	 World			(void);
	virtual		~World			(void);

	void		Initialize		(const CShIdentifier & levelIdentifier);
	void		Release			(void);

	void		Update			(float dt);

	bool		RegisterWorldListener	(IWorldListener * pListener);
	bool		UnregisterWorldListener	(IWorldListener * pListener);

	bool		CanCreateTowerAtPos		(const CShVector2 & position);
	void		CreateTower				(const CShVector2 & position, TowerBase::ETowerType towerType);

	void		SetGameSpeed	(float fGameSpeed);

	void		LooseHP			(void);
	void		GainHP			(void);

	void		LooseMoney		(int iAmountToLoose);
	void		GainMoney		(int iAmountToGain);

private:

	PluginInputManager	m_inputManager;

	WaveManager			m_waveManager;
	EnemyManager		m_enemyManager;
	TowerManager		m_towerManager;

	ShSound::Handle		m_soundHandle;

	CShIdentifier		m_levelIdentifier;

	float				m_fGameSpeed;
	int					m_iHP;
	int					m_iMoney;

	IWorldListener *	m_pWorldListener;
};


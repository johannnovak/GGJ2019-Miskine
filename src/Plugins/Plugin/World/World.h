#pragma once

#include "InputManager.h"
#include "Wave/WaveManager.h"
#include "Enemy/EnemyManager.h"
#include "Tower/TowerManager.h"

#include "IWorldListener.h"

#define DEFAULT_HP_DIFFICULTY_LOW 20
#define DEFAULT_HP_DIFFICULTY_MEDIUM 15
#define DEFAULT_HP_DIFFICULTY_HIGH 10

#define DEFAULT_MONEY_DIFFICULTY_LOW 1500
#define DEFAULT_MONEY_DIFFICULTY_MEDIUM 10000
#define DEFAULT_MONEY_DIFFICULTY_HIGH 500

class World
{
public:

	explicit				 World				(void);
	virtual					~World				(void);

	void					Initialize			(const CShIdentifier & levelIdentifier);
	void					Release				(void);

	void					Reset				(void);

	void					Update				(float dt);

	bool					RegisterWorldListener	(IWorldListener * pListener);
	bool					UnregisterWorldListener	(IWorldListener * pListener);

	bool					IsTowerAtPos			(const CShVector2 & position, TowerBase * & pTowerOut);
	bool					CanCreateTowerAtPos		(const CShVector2 & position);
	void					CreateTower				(const CShVector2 & position, TowerBase::ETowerType towerType);
	void					UpgradeTower			(TowerBase * pTower);
	void					SellTower				(TowerBase * pTower);

	EnemyManager &			GetEnemyManager		(void);
	TowerManager &			GetTowerManager		(void);

	void					SetGameSpeed	(float fGameSpeed);
	void					SetWave			(int iWave);

	void					LooseHP			(void);
	void					GainHP			(void);

	void					LooseMoney		(int iAmountToLoose);
	void					GainMoney		(int iAmountToGain);

	int	GetMoney() const
	{
		return m_iMoney;
	}

private:

	PluginInputManager		m_inputManager;

	WaveManager				m_waveManager;
	EnemyManager			m_enemyManager;
	TowerManager			m_towerManager;

	ShSound::Handle			m_soundHandle;
	CShIdentifier			m_levelIdentifier;

	float					m_fGameSpeed;
	int						m_iWave;
	int						m_iHP;
	int						m_iMoney;
public:
	IWorldListener *	m_pWorldListener;
};


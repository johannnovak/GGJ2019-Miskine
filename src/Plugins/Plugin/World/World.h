#pragma once

#include "InputManager.h"
#include "Wave/WaveManager.h"
#include "Enemy/EnemyManager.h"
#include "Tower/TowerManager.h"

class World
{
public:

	explicit	 World			(void);
	virtual		~World			(void);

	void		Initialize		(const CShIdentifier & levelIdentifier);
	void		Release			(void);

	void		Update			(float dt);

	void		CreateTower		(const CShVector2 & position);

	void		SetGameSpeed	(float fGameSpeed);

private:

	PluginInputManager	m_inputManager;

	WaveManager			m_waveManager;
	EnemyManager		m_enemyManager;
	TowerManager		m_towerManager;

	float				m_fGameSpeed;

	ShSound::Handle		m_soundHandle;

	CShIdentifier		m_levelIdentifier;
};


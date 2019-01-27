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

	bool		CanCreateTowerAtPos		(const CShVector2 & position);
	void		CreateTower				(const CShVector2 & position, TowerBase::ETowerType towerType);

	void		SetGameSpeed	(float fGameSpeed);

private:

	PluginInputManager	m_inputManager;

	WaveManager			m_waveManager;
	EnemyManager		m_enemyManager;
	TowerManager		m_towerManager;

	float				m_fGameSpeed;

	CShIdentifier		m_levelIdentifier;
};


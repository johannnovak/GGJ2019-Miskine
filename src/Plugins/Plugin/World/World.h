#pragma once

#include "InputManager.h"
#include "Wave/WaveManager.h"
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

private:

	PluginInputManager	m_inputManager;

	WaveManager			m_waveManager;
	TowerManager		m_towerManager;
};


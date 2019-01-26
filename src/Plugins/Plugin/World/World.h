#pragma once

#include "InputManager.h"
#include "Enemy/EnemyManager.h"
#include "Tower/TowerManager.h"

class World
{
public:

	explicit	 World			(void);
	virtual		~World			(void);

	void		Initialize		(void);
	void		Release			(void);

	void		Update			(float dt);

	void		CreateTower		(const CShVector2 & position);

private:

	PluginInputManager	m_inputManager;

	EnemyManager		m_enemyManager;
	TowerManager		m_towerManager;
};


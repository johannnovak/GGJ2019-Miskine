#pragma once

#include "InputManager.h"
#include "Enemy.h"

class World
{
public:

	explicit	 World			(void);
	virtual		~World			(void);

	void		Initialize		(void);
	void		Release			(void);

	void		Update			(float dt);

private:

	PluginInputManager	m_inputManager;

	Enemy *				m_pEnemy;
};


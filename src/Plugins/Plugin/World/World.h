#pragma once

#include "InputManager.h"

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
};


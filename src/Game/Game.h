#pragma once

#include "GameStates/GameStateGame.h"
#include "GameStates/GameStateMainMenu.h"

class Game
{
public:

	enum EState
	{
		MAIN_MENU,
		INGAME,

		MAX_GAME_STATES
	};

	static inline Game & GetInstance(void)
	{
		return(m_Instance);
	}

	void Initialize();
	void Release();

	void Update(float dt);

	//
	// States
	void		push				(EState state);
	void		pop					(void);
	GameState *	get					(EState state);

private:

	explicit Game(void);

private:

	static Game m_Instance;

	GameState *				m_aStates [MAX_GAME_STATES];
	int						m_iCurrentState;

	GameStateMainMenu		m_stateMainMenu;
	GameStateGame			m_stateGame;
};

#include "Game.inl"

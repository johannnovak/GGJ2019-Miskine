#pragma once

#include "GameStates/GameStateGame.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateCharacterIntro.h"
#include "GameStates/GameStateSettings.h"

#define ORIGINAL_VIEWPORT_X 1280.0f
#define ORIGINAL_VIEWPORT_Y 720.0f

class CShVector2;

class Game
{
public:

	enum EState
	{
		MAIN_MENU,
		CHARACTER_INTRO,
		SETTINGS,
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
	// Events
	void		touchBegin			(const CShVector2 & pos);
	void		touchEnd			(const CShVector2 & pos);
	void		touchMove			(const CShVector2 & pos);

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
	GameStateCharacterIntro	m_stateCharacterIntro;
	GameStateSettings		m_stateSettings;
	GameStateGame			m_stateGame;

	float m_fRatio;
};

#include "Game.inl"

#include "Game.h"

#include <ShSDK/ShSDK.h>

Game Game::m_Instance;

/**
 * @brief Game::Game
 */
Game::Game(void) : m_iCurrentState(-1)
{
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		m_aStates[i] = shNULL;
	}
}

/**
 * @brief Game::Initialize
 */
void Game::Initialize(void)
{
	//
	// Initialize states
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		get(EState(i))->init();
	}

	//
	// push Main Menu
	push(INGAME);
}

/**
 * @brief Game::Release
 */
void Game::Release(void)
{
	//
	// pop Main Menu
	pop();

	//
	// Release states
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		get(EState(i))->release();
	}
}

/**
 * @brief Game::Update
 * @param dt
 */
void Game::Update(float dt)
{
	m_aStates[m_iCurrentState]->update(dt);
}

/**
 * @brief Game::push
 * @param state
 */
void Game::push(EState state)
{
	SH_ASSERT(m_iCurrentState < MAX_GAME_STATES);

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->obscuring();
	}

	++m_iCurrentState;

	m_aStates[m_iCurrentState] = get(state);

	m_aStates[m_iCurrentState]->entered();
}

/**
 * @brief Game::pop
 */
void Game::pop(void)
{
	SH_ASSERT(m_iCurrentState >= 0);

	m_aStates[m_iCurrentState]->exiting();

#if SH_DEBUG
	m_aStates[m_iCurrentState] = nullptr;
#endif

	--m_iCurrentState;

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->revealed();
	}
}

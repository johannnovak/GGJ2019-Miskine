#include "Game.h"

#include <ShSDK/ShSDK.h>

Game Game::m_Instance;

/**
 * @brief Game::Game
 */
Game::Game(void)
: m_aStates()
, m_iCurrentState(-1)
, m_stateMainMenu()
, m_stateCharacterIntro()
, m_stateSettings()
, m_stateCredits()
, m_stateGame()
, m_stateGameOver()
, m_fRatio()
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


	int display_width = ShDisplay::GetWidth();
	int display_height = ShDisplay::GetHeight();

	float ratio_x = ORIGINAL_VIEWPORT_X / display_width;
	float ratio_y = ORIGINAL_VIEWPORT_Y / display_height;

	m_fRatio = shMax(ratio_x, ratio_y, 2.0f);

	//
	// Initialize states
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		get(EState(i))->init();
	}

	//
	// push Main Menu
	push(MAIN_MENU);
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
 * @brief Game::touchBegin
 */
void Game::touchBegin(const CShVector2 & pos)
{
	m_aStates[m_iCurrentState]->touchBegin(pos, m_fRatio);
}

/**
 * @brief Game::touchEnd
 */
void Game::touchEnd(const CShVector2 & pos)
{
	m_aStates[m_iCurrentState]->touchEnd(pos, m_fRatio);
}

/**
 * @brief Game::touchMove
 */
void Game::touchMove(const CShVector2 & pos)
{
	m_aStates[m_iCurrentState]->touchMove(pos, m_fRatio);
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

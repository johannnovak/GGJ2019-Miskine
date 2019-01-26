#include "GameStateGame.h"

#include "../Game.h"

#include "Plugin.h"
#include "PluginFactory.h"

/**
* @brief GameStateGame::Constructor
*/
GameStateGame::GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Destructor
*/
GameStateGame::~GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Initialize
*/
void GameStateGame::init(void)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	// ...
}

/**
* @brief GameStateGame::entered
*/
void GameStateGame::entered(void)
{
	if (!ShLevel::Load(CShIdentifier("level_test_pathfinding")))
	{
		SH_ASSERT_ALWAYS();
	}
}

/**
* @brief GameStateGame::exiting
*/
void GameStateGame::exiting(void)
{
	// ...
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::obscuring(void)
{
	// ...
}

/**
* @brief GameStateGame::revealed
*/
void GameStateGame::revealed(void)
{
	// ...
}

/**
* @brief GameStateGame::update
*/
void GameStateGame::update(float dt)
{
	// ...
}

/**
 * @brief GameStateGame::touchBegin
 */
void GameStateGame::touchBegin(const CShVector2 & pos_, float ratio)
{
	// ...
}

/**
 * @brief GameStateGame::touchEnd
 */
void GameStateGame::touchEnd(const CShVector2 & pos_, float ratio)
{
	// ...
}

/**
 * @brief GameStateGame::touchMove
 */
void GameStateGame::touchMove(const CShVector2 & pos_, float ratio)
{
	// ...
}

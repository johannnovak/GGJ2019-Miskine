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
	CShString strSuffix("_in_game");
	ShGUI::LoadGUIAndSSS(CShIdentifier("in_game"), ShGUI::GetRootControl(), strSuffix);
	m_pMainPanel = static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("in_game").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pMainPanel);
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	ShGUIControl::RemoveFromParent(m_pMainPanel);
}

/**
* @brief GameStateGame::entered
*/
void GameStateGame::entered(void)
{
	if (!ShLevel::Load(CShIdentifier("level_test_pathfinding2")))
	{
		SH_ASSERT_ALWAYS();
	}
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
* @brief GameStateGame::exiting
*/
void GameStateGame::exiting(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::obscuring(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
* @brief GameStateGame::revealed
*/
void GameStateGame::revealed(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
* @brief GameStateGame::update
*/
void GameStateGame::update(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief GameStateGame::touchBegin
 */
void GameStateGame::touchBegin(const CShVector2 & pos_, float ratio)
{
	TouchDownPlugin(0, pos_.m_x, pos_.m_y);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateGame::touchEnd
 */
void GameStateGame::touchEnd(const CShVector2 & pos_, float ratio)
{
	TouchUpPlugin(0, pos_.m_x, pos_.m_y);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateGame::touchMove
 */
void GameStateGame::touchMove(const CShVector2 & pos_, float ratio)
{
	TouchMovePlugin(0, pos_.m_x, pos_.m_y);
	SH_UNUSED(ratio);
}

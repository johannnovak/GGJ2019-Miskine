#include "GameStateGameOver.h"

#include "../Game.h"

/**
 * @brief Constructor
 */
GameStateGameOver::GameStateGameOver(void)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateGameOver::~GameStateGameOver(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateGameOver::init(void)
{
	CShString strSuffix("_game_over");
	ShGUI::LoadGUIAndSSS(CShIdentifier("game_over"), ShGUI::GetRootControl(), strSuffix);
	m_pMainPanel = static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("game_over").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pMainPanel);
	ShGUIControlPanel::Hide(m_pMainPanel);
	ShGUIControlButton * pOkButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_ok").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pOkButton, ButtonOkClicked);
}

/**
 * @brief Release
 */
void GameStateGameOver::release(void)
{
	ShGUIControl::RemoveFromParent(m_pMainPanel);
}

/**
 * @brief entered
 */
void GameStateGameOver::entered(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief exiting
 */
void GameStateGameOver::exiting(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief obscuring
 */
void GameStateGameOver::obscuring(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief revealed
 */
void GameStateGameOver::revealed(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief update
 */
void GameStateGameOver::update(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief GameStateGameOver::Release
 */
void GameStateGameOver::touchBegin(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateGameOver::Release
 */
void GameStateGameOver::touchEnd(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateGameOver::Release
 */
void GameStateGameOver::touchMove(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateGameOver::ButtonOkClicked
 * @param pControl
 * @param vPosition
 * @return
 */
/*static*/ bool GameStateGameOver::ButtonOkClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	ShApplication::RequestQuit();
	return true;
}

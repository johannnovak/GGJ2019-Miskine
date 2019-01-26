#include "GameStateMainMenu.h"

#include "../Game.h"

bool ButtonNewGameClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	Game::GetInstance().pop();
	Game::GetInstance().push(Game::CHARACTER_INTRO);
	return true;
}

bool ButtonSettingsClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	Game::GetInstance().push(Game::SETTINGS);
	return true;
}

bool ButtonCreditsClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	Game::GetInstance().push(Game::CREDITS);
	return true;
}


/**
 * @brief Constructor
 */
GameStateMainMenu::GameStateMainMenu(void)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateMainMenu::~GameStateMainMenu(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateMainMenu::init(void)
{
	CShString strSuffix("_main_menu");
	ShGUI::LoadGUIAndSSS(CShIdentifier("main_menu"), ShGUI::GetRootControl(), strSuffix);
	m_pMainPanel = static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("main_menu").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pMainPanel);
	ShGUIControlPanel::Hide(m_pMainPanel);
	ShGUIControlButton * pNewGameButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_new_game").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pNewGameButton, ButtonNewGameClicked);
	ShGUIControlButton * pSettingsButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_settings").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pSettingsButton, ButtonSettingsClicked);
	ShGUIControlButton * pCreditsButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_credits").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pCreditsButton, ButtonCreditsClicked);
}

/**
 * @brief Release
 */
void GameStateMainMenu::release(void)
{
	ShGUIControl::RemoveFromParent(m_pMainPanel);
}

/**
 * @brief entered
 */
void GameStateMainMenu::entered(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief exiting
 */
void GameStateMainMenu::exiting(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief obscuring
 */
void GameStateMainMenu::obscuring(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief revealed
 */
void GameStateMainMenu::revealed(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief update
 */
void GameStateMainMenu::update(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchBegin(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchEnd(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchMove(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

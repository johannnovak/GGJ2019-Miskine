#include "GameStateSettings.h"

#include "../Game.h"

bool ButtonCancelClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	Game::GetInstance().pop();
	return true;
}


/**
 * @brief Constructor
 */
GameStateSettings::GameStateSettings(void)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateSettings::~GameStateSettings(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateSettings::init(void)
{
	CShString strSuffix("_settings");
	ShGUI::LoadGUIAndSSS(CShIdentifier("settings"), ShGUI::GetRootControl(), strSuffix);
	m_pMainPanel = static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("settings").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pMainPanel);
	ShGUIControlPanel::Hide(m_pMainPanel);
	ShGUIControlButton * pCancelButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_cancel").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pCancelButton, ButtonCancelClicked);
}

/**
 * @brief Release
 */
void GameStateSettings::release(void)
{
	ShGUIControl::RemoveFromParent(m_pMainPanel);
}

/**
 * @brief entered
 */
void GameStateSettings::entered(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief exiting
 */
void GameStateSettings::exiting(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief obscuring
 */
void GameStateSettings::obscuring(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief revealed
 */
void GameStateSettings::revealed(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief update
 */
void GameStateSettings::update(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief GameStateSettings::Release
 */
void GameStateSettings::touchBegin(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateSettings::Release
 */
void GameStateSettings::touchEnd(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateSettings::Release
 */
void GameStateSettings::touchMove(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

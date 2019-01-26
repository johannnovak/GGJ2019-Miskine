#include "GameStateCharacterIntro.h"

#include "../Game.h"

bool ButtonPlayClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	Game::GetInstance().pop();
	Game::GetInstance().push(Game::INGAME);
	return true;
}

/**
 * @brief Constructor
 */
GameStateCharacterIntro::GameStateCharacterIntro(void)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateCharacterIntro::~GameStateCharacterIntro(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateCharacterIntro::init(void)
{
	CShString strSuffix("_introduction");
	ShGUI::LoadGUIAndSSS(CShIdentifier("introduction"), ShGUI::GetRootControl(), strSuffix);
	m_pMainPanel = static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("introduction").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pMainPanel);
	ShGUIControlPanel::Hide(m_pMainPanel);
	ShGUIControlButton * pPlayButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_start").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pPlayButton, ButtonPlayClicked);
}

/**
 * @brief Release
 */
void GameStateCharacterIntro::release(void)
{
	ShGUIControl::RemoveFromParent(m_pMainPanel);
}

/**
 * @brief entered
 */
void GameStateCharacterIntro::entered(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief exiting
 */
void GameStateCharacterIntro::exiting(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief obscuring
 */
void GameStateCharacterIntro::obscuring(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief revealed
 */
void GameStateCharacterIntro::revealed(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief update
 */
void GameStateCharacterIntro::update(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief GameStateCharacterIntro::Release
 */
void GameStateCharacterIntro::touchBegin(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateCharacterIntro::Release
 */
void GameStateCharacterIntro::touchEnd(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateCharacterIntro::Release
 */
void GameStateCharacterIntro::touchMove(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

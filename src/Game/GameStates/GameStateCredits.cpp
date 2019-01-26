#include "GameStateCredits.h"

#include "../Game.h"

bool ButtonOkClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);
	Game::GetInstance().pop();
	return true;
}


/**
 * @brief Constructor
 */
GameStateCredits::GameStateCredits(void)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateCredits::~GameStateCredits(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateCredits::init(void)
{
	CShString strSuffix("_credits");
	ShGUI::LoadGUIAndSSS(CShIdentifier("credits"), ShGUI::GetRootControl(), strSuffix);
	m_pMainPanel = static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("credits").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pMainPanel);
	ShGUIControlPanel::Hide(m_pMainPanel);
	ShGUIControlButton * pOkButton = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_ok").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlButton::AddSignalFctPtrClick(pOkButton, ButtonOkClicked);
}

/**
 * @brief Release
 */
void GameStateCredits::release(void)
{
	ShGUIControl::RemoveFromParent(m_pMainPanel);
}

/**
 * @brief entered
 */
void GameStateCredits::entered(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief exiting
 */
void GameStateCredits::exiting(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief obscuring
 */
void GameStateCredits::obscuring(void)
{
	ShGUIControlPanel::Hide(m_pMainPanel);
}

/**
 * @brief revealed
 */
void GameStateCredits::revealed(void)
{
	ShGUIControlPanel::Show(m_pMainPanel);
}

/**
 * @brief update
 */
void GameStateCredits::update(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief GameStateCredits::Release
 */
void GameStateCredits::touchBegin(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateCredits::Release
 */
void GameStateCredits::touchEnd(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

/**
 * @brief GameStateCredits::Release
 */
void GameStateCredits::touchMove(const CShVector2 & pos, float ratio)
{
	SH_UNUSED(pos);
	SH_UNUSED(ratio);
}

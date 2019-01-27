#include "GameStateGame.h"

#include "../Game.h"

#include "Plugin.h"
#include "PluginFactory.h"

/**
* @brief GameStateGame::Constructor
*/
GameStateGame::GameStateGame(void)
: m_pMainPanel(shNULL)
, m_pWaveCurrent(shNULL)
, m_pWaveTotal(shNULL)
, m_pUserName(shNULL)
, m_pMoneyValue(shNULL)
, m_pHPValue(shNULL)
, m_pMHPTotal(shNULL)
, m_pPause(shNULL)
, m_pPlay(shNULL)
, m_pFastForward(shNULL)
, m_pMenu(shNULL)
, m_amepModeImages()
, m_pEditBoxHidden(shNULL)
, m_pTextPopup(shNULL)
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
	ShGUIControlImage * pImage = shNULL;

	pImage = static_cast<ShGUIControlImage*>(ShGUIControl::GetElementById(CShIdentifier("image_f1").Append(strSuffix.Get()), m_pMainPanel));
	m_amepModeImages.Add( EPlayer2EventType::e_player2_event_type_type_words, pImage);
	pImage = static_cast<ShGUIControlImage*>(ShGUIControl::GetElementById(CShIdentifier("image_f2").Append(strSuffix.Get()), m_pMainPanel));
	m_amepModeImages.Add( EPlayer2EventType::e_player2_event_type_random_keys, pImage);
	pImage = static_cast<ShGUIControlImage*>(ShGUIControl::GetElementById(CShIdentifier("image_f3").Append(strSuffix.Get()), m_pMainPanel));
	m_amepModeImages.Add( EPlayer2EventType::e_player2_event_type_dual_key_combination_streak, pImage);
	pImage = static_cast<ShGUIControlImage*>(ShGUIControl::GetElementById(CShIdentifier("image_f4").Append(strSuffix.Get()), m_pMainPanel));
	m_amepModeImages.Add( EPlayer2EventType::e_player2_event_type_mental_calculation, pImage);
	pImage = static_cast<ShGUIControlImage*>(ShGUIControl::GetElementById(CShIdentifier("image_f5").Append(strSuffix.Get()), m_pMainPanel));
	m_amepModeImages.Add( EPlayer2EventType::e_player2_event_type_immediate_qte, pImage);
	pImage = static_cast<ShGUIControlImage*>(ShGUIControl::GetElementById(CShIdentifier("image_f6").Append(strSuffix.Get()), m_pMainPanel));
	m_amepModeImages.Add( EPlayer2EventType::e_player2_event_type_super_mega_combo, pImage);

	m_pWaveCurrent = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_wave_current").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pWaveCurrent);
	m_pWaveTotal = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_wave_current").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pWaveTotal);
	m_pUserName = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_username").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pUserName);
	m_pMoneyValue = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_money_value").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pMoneyValue);
	m_pHPValue = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_hp_value").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pHPValue);
	m_pMHPTotal = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_hp_total").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pMHPTotal);
	m_pPause = static_cast<ShGUIControlRadioButton*>(ShGUIControl::GetElementById(CShIdentifier("radiobutton_pause").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pPause);
	m_pPlay = static_cast<ShGUIControlRadioButton*>(ShGUIControl::GetElementById(CShIdentifier("radiobutton_play").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pPlay);
	m_pFastForward = static_cast<ShGUIControlRadioButton*>(ShGUIControl::GetElementById(CShIdentifier("radiobutton_fast_forward").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pFastForward);
	m_pMenu = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_menu").Append(strSuffix.Get()), m_pMainPanel));
	SH_ASSERT(shNULL != m_pMenu);


	m_pEditBoxHidden = static_cast<ShGUIControlEditBox*>(ShGUIControl::GetElementById(CShIdentifier("editbox_hidden").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pEditBoxHidden);

	m_pTextPopup = static_cast<ShGUIControlText*>(ShGUIControl::GetElementById(CShIdentifier("text_popup").Append(strSuffix.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pTextPopup);

	//
	// Set Slots
	ShGUIControlButton::AddSignalFctPtrClick(m_pMenu,				(pSignalSDKClick)GameStateGame::OnGUIMenuClicked);
	ShGUIControlRadioButton::AddSlotFctPtrSelected(m_pPause,		(pSlotSDKButtonSelected)GameStateGame::OnGUIPauseSelected);
	ShGUIControlRadioButton::AddSlotFctPtrSelected(m_pPlay,			(pSlotSDKButtonSelected)GameStateGame::OnGUIPlaySelected);
	ShGUIControlRadioButton::AddSlotFctPtrSelected(m_pFastForward,	(pSlotSDKButtonSelected)GameStateGame::OnGUIFastForwardSelected);

	//
	// Mouse catching
	ShGUIControlPanel * pPanelHeader	= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_header").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelF1		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_F1").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelF2		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_F2").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelF3		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_F3").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelF4		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_F4").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelF5		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_F5").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelF6		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_F6").Append(strSuffix.Get()), m_pMainPanel));
	ShGUIControlPanel * pPanelRight		= static_cast<ShGUIControlPanel*>(ShGUIControl::GetElementById(CShIdentifier("panel_Right").Append(strSuffix.Get()), m_pMainPanel));

	ShGUIControl::SetIgnoreEvents(pPanelHeader, false);
	ShGUIControl::SetIgnoreEvents(pPanelF1, false);
	ShGUIControl::SetIgnoreEvents(pPanelF2, false);
	ShGUIControl::SetIgnoreEvents(pPanelF3, false);
	ShGUIControl::SetIgnoreEvents(pPanelF4, false);
	ShGUIControl::SetIgnoreEvents(pPanelF5, false);
	ShGUIControl::SetIgnoreEvents(pPanelF6, false);
	ShGUIControl::SetIgnoreEvents(pPanelRight, false);
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	ShGUIControl::RemoveFromParent(m_pEditBoxHidden);
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

	//
	// Register variables for Player2EventManager
	Player2EventManager::GetInstance().RegisterEditBoxHidden(m_pEditBoxHidden);
	Player2EventManager::GetInstance().RegisterListener(this);

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

/**
 * @brief GameStateGame::OnEventTypeAvailable
 * @param pEvent
 */
void GameStateGame::OnEventTypeAvailable(Player2Event *pEvent)
{
	ShGUIControlImage * pControlPanel = *m_amepModeImages.Find(pEvent->GetType());
	ShGUIControlImage::SetSpriteColorFilter(pControlPanel, CShRGBAf_WHITE);
}

/**
 * @brief GameStateGame::OnEventTypeUnavailable
 * @param pEvent
 */
void GameStateGame::OnEventTypeUnavailable(Player2Event *pEvent)
{
	ShGUIControlImage * pControlPanel = *m_amepModeImages.Find(pEvent->GetType());
	ShGUIControlImage::SetSpriteColorFilter(pControlPanel, CShRGBAf_RED);
}

/**
 * @brief GameStateGame::OnEventTypeBegin
 * @param pEvent
 */
void GameStateGame::OnEventTypeBegin(Player2Event *pEvent)
{
	ShGUIControlImage * pControlPanel = *m_amepModeImages.Find(pEvent->GetType());
	ShGUIControlImage::SetSpriteColorFilter(pControlPanel, CShRGBAf_WHITE);
	switch (pEvent->GetType())
	{
		case e_player2_event_type_type_words:
		{
			Player2EventTypeWords * pCastedEvent = static_cast<Player2EventTypeWords*>(pEvent);
			ShGUIControlText::SetText(m_pTextPopup, pCastedEvent->GetWordToType());
			break;
		}
		default:
		{
			break;
		}
	}
}

/**
 * @brief GameStateGame::OnEventTypeEnd
 * @param pEvent
 */
void GameStateGame::OnEventTypeEnd(Player2Event *pEvent)
{
	ShGUIControlImage * pControlPanel = *m_amepModeImages.Find(pEvent->GetType());
	ShGUIControlImage::SetSpriteColorFilter(pControlPanel, CShRGBAf_RED);
}

/**
 * @brief GameStateGame::OnEventTypeFinished
 * @param pEvent
 */
void GameStateGame::OnEventTypeFinished(Player2Event *pEvent)
{
	ShGUIControlImage * pControlPanel = *m_amepModeImages.Find(pEvent->GetType());
	ShGUIControlImage::SetSpriteColorFilter(pControlPanel, CShRGBAf_RED);
}

/**
 * @brief GameStateGame::OnTypoGaugeUpdated
 * @param fNormedValue
 */
void GameStateGame::OnTypoGaugeUpdated(float fNormedValue)
{
	SH_UNUSED(fNormedValue);
}

/**
 * @brief GameStateGame::OnTypoGaugeFilled
 */
void GameStateGame::OnTypoGaugeFilled(void)
{

}

/**
 * @brief GameStateGame::OnTypoGaugeEmptied
 */
void GameStateGame::OnTypoGaugeEmptied(void)
{

}

/**
 * @brief GameStateGame::OnEventTypeTypeWordCharacterOK
 * @param iCharacterIndexOK
 */
void GameStateGame::OnEventTypeTypeWordCharacterOK(int iCharacterIndexOK)
{
	SH_UNUSED(iCharacterIndexOK);
}

/**
 * @brief GameStateGame::OnEventTypeTypeWordCharacterNOK
 * @param iCharacterIndexNOK
 */
void GameStateGame::OnEventTypeTypeWordCharacterNOK(int iCharacterIndexNOK)
{
	SH_UNUSED(iCharacterIndexNOK);
}

/**
 * @brief GameStateGame::OnEventTypeRewardUserPireCoin
 * @param iPeerCoinAmount
 */
void GameStateGame::OnEventTypeRewardUserPireCoin(int iPeerCoinAmount)
{
	ShGUIControlText::SetText(m_pMoneyValue, CShString::FromInt(ShGUIControlText::GetText(m_pMoneyValue).AsInt() + iPeerCoinAmount));
}

/**
 * @brief GameStateGame::OnEventTypeRewardUserHP
 * @param iHPBonus
 */
void GameStateGame::OnEventTypeRewardUserHP(int iHPBonus)
{
	ShGUIControlText::SetText(m_pHPValue, CShString::FromInt(ShGUIControlText::GetText(m_pHPValue).AsInt() + iHPBonus));
}

/**
 * @brief GameStateGame::OnEventTypeRewardGameSlowMotion
 * @param fSlowMotionFactor
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeRewardGameSlowMotion(float fSlowMotionFactor, float fDurationTime)
{
	SH_UNUSED(fSlowMotionFactor);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeRewardTowerAttack
 * @param iBonusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeRewardTowerAttack(int iBonusValue, float fDurationTime)
{
	SH_UNUSED(iBonusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeRewardTowerAttackSpeed
 * @param iBonusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeRewardTowerAttackSpeed(int iBonusValue, float fDurationTime)
{
	SH_UNUSED(iBonusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeRewardTowerRadius
 * @param iBonusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeRewardTowerRadius(int iBonusValue, float fDurationTime)
{
	SH_UNUSED(iBonusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeRewardTowerAttackAOE
 * @param iBonusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeRewardTowerAttackAOE(int iBonusValue, float fDurationTime)
{
	SH_UNUSED(iBonusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeMalusUserHP
 * @param iHPMalus
 */
void GameStateGame::OnEventTypeMalusUserHP(int iHPMalus)
{
	ShGUIControlText::SetText(m_pHPValue, CShString::FromInt(ShGUIControlText::GetText(m_pHPValue).AsInt() - iHPMalus));
}

/**
 * @brief GameStateGame::OnEventTypeMalusGameFastForward
 * @param iFastForwardFactor
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeMalusGameFastForward(float iFastForwardFactor, float fDurationTime)
{
	SH_UNUSED(iFastForwardFactor);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeMalusGameNewEnemy
 * @param iEnemyCount
 */
void GameStateGame::OnEventTypeMalusGameNewEnemy(int iEnemyCount)
{
	SH_UNUSED(iEnemyCount);
}

/**
 * @brief GameStateGame::OnEventTypeMalusGameNewWave
 * @param iWaveCount
 */
void GameStateGame::OnEventTypeMalusGameNewWave(int iWaveCount)
{
	SH_UNUSED(iWaveCount);
}

/**
 * @brief GameStateGame::OnEventTypeMalusTowerAttack
 * @param iMalusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeMalusTowerAttack(int iMalusValue, float fDurationTime)
{
	SH_UNUSED(iMalusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeMalusTowerAttackSpeed
 * @param iMalusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeMalusTowerAttackSpeed(int iMalusValue, float fDurationTime)
{
	SH_UNUSED(iMalusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeMalusTowerRadius
 * @param iMalusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeMalusTowerRadius(int iMalusValue, float fDurationTime)
{
	SH_UNUSED(iMalusValue);
	SH_UNUSED(fDurationTime);
}

/**
 * @brief GameStateGame::OnEventTypeMalusTowerAttackAOE
 * @param iMalusValue
 * @param fDurationTime
 */
void GameStateGame::OnEventTypeMalusTowerAttackAOE(int iMalusValue, float fDurationTime)
{
	SH_UNUSED(iMalusValue);
	SH_UNUSED(fDurationTime);
}


/**
 * @brief GameStateGame::OnEventTypeMalusTowerAttackAOE
 */
/*virtual*/ void GameStateGame::OnTowerCreated(void)
{
	// ...
}

/**
 * @brief GameStateGame::OnEventTypeMalusTowerAttackAOE
 */
/*virtual*/ void GameStateGame::OnMoneyUpdated(int iMoneyAmount)
{
	ShGUIControlText::SetText(m_pMoneyValue, CShString::FromInt(iMoneyAmount));
}

/**
 * @brief GameStateGame::OnEventTypeMalusTowerAttackAOE
 */
/*virtual*/ void GameStateGame::OnHPUpdated(int iHPAmount)
{
	ShGUIControlText::SetText(m_pHPValue, CShString::FromInt(iHPAmount));
}

/**
 * @brief GameStateGame::OnGUIMenuClicked
 */
/*static*/ bool GameStateGame::OnGUIMenuClicked(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	// TODO
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);

	return false;
}

/**
 * @brief GameStateGame::OnGUIPauseClicked
 *//*static*/ bool GameStateGame::OnGUIPauseSelected(ShGUIControl * pControl)
{
	SH_UNUSED(pControl);

	static_cast<Plugin*>(GetPlugin())->GetWorld().SetGameSpeed(0.0f);

	return true;
}

/**
 * @brief GameStateGame::OnGUIPlayClicked
 *//*static*/ bool GameStateGame::OnGUIPlaySelected(ShGUIControl * pControl)
{
	SH_UNUSED(pControl);

	static_cast<Plugin*>(GetPlugin())->GetWorld().SetGameSpeed(1.0f);

	return true;
}

/**
 * @brief GameStateGame::OnGUIFastForwardClicked
 */
/*static*/ bool GameStateGame::OnGUIFastForwardSelected(ShGUIControl * pControl)
{
	SH_UNUSED(pControl);

	static_cast<Plugin*>(GetPlugin())->GetWorld().SetGameSpeed(2.0f);

	return true;
}
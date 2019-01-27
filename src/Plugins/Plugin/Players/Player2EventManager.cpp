#include "Player2EventManager.h"

/*static*/ Player2EventManager Player2EventManager::s_Player2EventManager;

/**
 * @brief GetInstance
 */
/*static*/ Player2EventManager & Player2EventManager::GetInstance(void)
{
	return Player2EventManager::s_Player2EventManager;
}

/**
 * @brief Initialize
 * @param pUser
 */
void Player2EventManager::Initialize(void)
{
	//
	// Initialization
	m_pCurrentEvent			= shNULL;
	m_pPreviousEvent		= shNULL;
	m_fTypoGaugeValue		= 0.0f;
	m_fTypoGaugeMax			= TYPO_GAUGE_DEFAULT_MAX_VALUE;
	m_pPlayer2EventListener	= shNULL;
	m_iCurrentEventStreak	= 0;
	m_pEditBoxHidden		= shNULL;

	//
	// Get User
	m_pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != m_pUser);

	//
	// Initialize events
	m_eventTypeWords.Initialize();
	//m_eventBoostTower.Initialize();
	//m_eventGrantSpecialAttack.Initialize();
	//m_eventControlEnemy.Initialize();
	//m_eventImmediateQTE.Initialize();
	//m_eventSuperMegaCombo.Initialize();

	//
	// Set up m_apEvent
	m_apEvents[e_player2_event_type_type_words]				= &m_eventTypeWords;
	//m_apEvents[e_player2_event_type_boost_tower]			= &m_eventBoostTower;
	//m_apEvents[e_player2_event_type_grant_special_attack]	= &m_eventGrantSpecialAttack;
	//m_apEvents[e_player2_event_type_control_enemy]			= &m_eventControlEnemy;
	//m_apEvents[e_player2_event_type_immediate_qte]			= &m_eventImmediateQTE;
	//m_apEvents[e_player2_event_type_super_mega_combo]		= &m_eventSuperMegaCombo;

	//
	// Initialize bool arrays
	ResetBoolArray(m_aAvailableEvents);
	ResetBoolArray(m_aJustCompletedEvents);
}

/**
 * @brief Release
 */
void Player2EventManager::Release(void)
{
	// ...
}

/**
 * @brief IsEventJustCompleted
 */
bool Player2EventManager::IsEventJustCompleted(EPlayer2EventType eEventType)
{
	return m_aJustCompletedEvents[eEventType];
}

/**
 * @brief IsEventJustCompleted
 */
Player2Event * Player2EventManager::GetCurrentEvent(void)
{
	return m_pCurrentEvent;
}

/**
 * @brief IsEventAvailable
 */
bool Player2EventManager::IsEventAvailable(EPlayer2EventType eEventType)
{
	return m_aAvailableEvents[eEventType];
}

/**
 * @brief ChooseEventType
 */
bool Player2EventManager::ChooseEventType(EPlayer2EventType eEventType)
{
	if (IsEventAvailable(eEventType))
	{
		//
		// Check for just completed not to increase error jauge by mistake
		m_pPreviousEvent = GetCurrentEvent();
		if (shNULL != m_pPreviousEvent && !IsEventJustCompleted(m_pPreviousEvent->GetType()))
		{
			IncreaseTypoGauge(m_pPreviousEvent->GetDifficulty());
		}

		//
		// Reset just completed as we start a new event and make available the old one
		ResetBoolArray(m_aJustCompletedEvents);
		
		//
		// Update current event index and remove the chosen one from the available ones
		m_pCurrentEvent = m_apEvents[eEventType];
		m_pCurrentEvent->Reset(m_iCurrentEventStreak);
		SetEventTypeUnavailable(m_pCurrentEvent->GetType());

		return true;
	}
	return false;
}

/**
 * @brief LeaveEventType
 */
bool Player2EventManager::LeaveEventType(void)
{
	if (shNULL != m_pCurrentEvent)
	{
		//
		// Check for just completed not to increase error jauge by mistake
		m_pPreviousEvent = GetCurrentEvent();
		if (!IsEventJustCompleted(m_pPreviousEvent->GetType()))
		{
			IncreaseTypoGauge(m_pPreviousEvent->GetDifficulty());
		}

		//
		// Reset just completed
		m_iCurrentEventStreak = 0;
		m_pPreviousEvent->Reset(m_iCurrentEventStreak);
		
		//
		// Update current event index
		m_pCurrentEvent = shNULL;

		return true;
	}
	return false;
}

/**
 * @brief RegisterListener
 */
bool Player2EventManager::RegisterListener(IPlayer2EventListener * pListener)
{
	if (shNULL == pListener)
	{
		return false;
	}

	m_pPlayer2EventListener = pListener;

	return true;
}

/**
 * @brief UnregisterListener
 */
bool Player2EventManager::UnregisterListener(IPlayer2EventListener * pListener)
{
	if (shNULL == pListener)
	{
		return false;
	}
	else if (m_pPlayer2EventListener != pListener)
	{
		return false;
	}
	else
	{
		m_pPlayer2EventListener = shNULL;

		return true;
	}
}

/**
 * @brief RegisterEditBoxHidden
 */
bool Player2EventManager::RegisterEditBoxHidden(ShGUIControlEditBox * pEditBox)
{
	if (shNULL == pEditBox)
	{
		return false;
	}

	m_pEditBoxHidden = pEditBox;

	return true;
}

/**
 * @brief UnregisterEditBoxHidden
 */
bool Player2EventManager::UnregisterEditBoxHidden(ShGUIControlEditBox * pEditBox)
{
	if (shNULL == pEditBox)
	{
		return false;
	}
	else if (m_pEditBoxHidden != pEditBox)
	{
		return false;
	}
	else
	{
		m_pEditBoxHidden = shNULL;

		return true;
	}
}

/**
 * @brief SetEventTypeAvailable
 */
void Player2EventManager::SetEventTypeAvailable(EPlayer2EventType eType)
{
	m_aAvailableEvents[eType] = true;

	//
	// Notify listeners
	if (shNULL != m_pPlayer2EventListener)
	{
		m_pPlayer2EventListener->OnEventTypeAvailable(m_apEvents[eType]);
	}
}

/**
 * @brief SetEventTypeUnavailable
 */
void Player2EventManager::SetEventTypeUnavailable(EPlayer2EventType eType)
{
	m_aAvailableEvents[eType] = false;

	//
	// Notify listeners
	if (shNULL != m_pPlayer2EventListener)
	{
		m_pPlayer2EventListener->OnEventTypeUnavailable(m_apEvents[eType]);
	}
}

/**
 * @brief PollNewEvents
 */
void Player2EventManager::PollNewEvents(float dt)
{
	//
	// Event TypeWord always accessible
	if (!m_aAvailableEvents[e_player2_event_type_type_words] && m_pCurrentEvent != m_apEvents[e_player2_event_type_type_words])
	{
		SetEventTypeAvailable(e_player2_event_type_type_words);
	}

	//
	// TODO : other events
}

/**
 * @brief OnCurrentEventFinished
 */
void Player2EventManager::OnCurrentEventFinished(void)
{
	m_aJustCompletedEvents[m_pCurrentEvent->GetType()] = true;

	//
	// Apply reward reforwarding from event
	// TODO=+
}

/**
 * @brief ResetBoolArray
 */
void Player2EventManager::ResetBoolArray(bool * aBool)
{
	memset(aBool, 0, sizeof(bool) * e_player2_event_type_count);
}	

/**
 * @brief Update
 */
void Player2EventManager::Update(float dt)
{
	//
	// Poll new events
	PollNewEvents(dt);

	//
	// Check state of current event
	if (shNULL != m_pCurrentEvent)
	{
		m_pCurrentEvent->Update(dt, m_pEditBoxHidden);
		if (m_pCurrentEvent->IsFinished())
		{
			//
			// Notify listeners on event finished
			if (shNULL != m_pPlayer2EventListener)
			{
				m_pPlayer2EventListener->OnEventTypeFinished(m_pCurrentEvent);
			}

			//
			// Reset EventType
			if (m_pCurrentEvent->GetErrorNb() == 0)
			{
				++m_iCurrentEventStreak;
			}
			else
			{
				m_iCurrentEventStreak = 0;
			}

			switch (m_pCurrentEvent->GetType())
			{
				//
				// Still available
				case e_player2_event_type_type_words:
				case e_player2_event_type_random_keys:
				{
					m_pCurrentEvent->Reset(m_iCurrentEventStreak);
				}
				break;

				//
				// Then unavailable
				case e_player2_event_type_mental_calculation:
				case e_player2_event_type_dual_key_combination_streak:
				case e_player2_event_type_immediate_qte:
				case e_player2_event_type_super_mega_combo:
				{
					m_pCurrentEvent->Reset(0);
					SetEventTypeUnavailable(m_pCurrentEvent->GetType());
				}
				break;
			}
		}
	}

	//
	// Handle user choice
	HandleUserChoice();

	//
	// Check typo jauge
	CheckTypoGaugeCompletion();
	
	if (shNULL != m_pEditBoxHidden)
	{
		ShGUIControlEditBox::SetText(m_pEditBoxHidden, CShString(""));
	}
}

/**
 * @brief HandleUserChoice
 */
void Player2EventManager::HandleUserChoice(void)
{
	if		(ShUser::HasTriggeredAction(m_pUser, CShIdentifier("escape")))
	{
		if (LeaveEventType())
		{
			//
			// Notify Listeners for canceled Event
			if (shNULL != m_pPlayer2EventListener)
			{
				m_pPlayer2EventListener->OnEventTypeEnd(m_pPreviousEvent);
			}
		}
	}
	else
	{
		bool bChanged;

		if (ShUser::HasTriggeredAction(m_pUser, CShIdentifier("f1")))
		{
			bChanged = ChooseEventType(e_player2_event_type_type_words);
		}
		//else if (ShUser::HasTriggeredAction(m_pUser, CShIdentifier("f2")))
		//{
		//	ChooseEventType(e_player2_event_type_boost_tower);
		//}
		//else if (ShUser::HasTriggeredAction(m_pUser, CShIdentifier("f3")))
		//{
		//	ChooseEventType(e_player2_event_type_grant_special_attack);
		//}
		//else if (ShUser::HasTriggeredAction(m_pUser, CShIdentifier("f4")))
		//{
		//	ChooseEventType(e_player2_event_type_control_enemy);
		//}
		//else if (ShUser::HasTriggeredAction(m_pUser, CShIdentifier("f5")))
		//{
		//	ChooseEventType(e_player2_event_type_super_mega_combo);
		//}
		else
		{
			bChanged = false;
		}

		if (bChanged)
		{
			//
			// Notify listeners the EventType has ended and has begun
			if (shNULL != m_pPlayer2EventListener)
			{
				if (shNULL != m_pPreviousEvent) { m_pPlayer2EventListener->OnEventTypeEnd(m_pPreviousEvent); }
				m_pPlayer2EventListener->OnEventTypeBegin(m_pCurrentEvent);
			}
		}
	}

}

/**
 * @brief HandleUserChoice
 */
void Player2EventManager::IncreaseTypoGauge(EPlayer2EventDifficulty eDifficulty)
{
	float fDelta = eDifficulty + 1;
	fDelta *= fDelta;
	m_fTypoGaugeValue += fDelta;
	m_fTypoGaugeValue = shMin(m_fTypoGaugeMax, m_fTypoGaugeValue);

	//
	// Notify listeners for updated
	if (shNULL != m_pPlayer2EventListener)
	{
		m_pPlayer2EventListener->OnTypoGaugeUpdated(m_fTypoGaugeValue / m_fTypoGaugeMax);
	}
}

/**
 * 
@brief HandleUserChoice
 */
void Player2EventManager::CheckTypoGaugeCompletion(void)
{
	if (m_fTypoGaugeValue >= m_fTypoGaugeMax)
	{
		//
		// Notify listeners for filled
		if (shNULL != m_pPlayer2EventListener)
		{
			m_pPlayer2EventListener->OnTypoGaugeFilled();
		}

		//
		// Reset typo gauge
		m_fTypoGaugeValue = 0.0f;
	}
}

/**
 * @brief Player2EventManager::Player2EventManager
 */
Player2EventManager::Player2EventManager(void)
: m_pUser(shNULL)
, m_apEvents()
, m_eventTypeWords()
, m_aAvailableEvents()
, m_aJustCompletedEvents()
, m_pCurrentEvent(shNULL)
, m_pPreviousEvent(shNULL)
, m_iCurrentEventStreak(0)
, m_fTypoGaugeValue(0.0f)
, m_fTypoGaugeMax(TYPO_GAUGE_DEFAULT_MAX_VALUE)
, m_pPlayer2EventListener(shNULL)
, m_pEditBoxHidden(shNULL)
{
}

#include "Player2EventManager.h"

/*static*/ Player2EventManager Player2EventManager::s_Player2EventManager;

/**
 * @brief GetInstance
 */
const Player2EventManager & Player2EventManager::GetInstance(void)
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
		if (!IsEventJustCompleted(m_pPreviousEvent->GetType()))
		{
			IncreaseTypoGauge(m_pPreviousEvent->GetDifficulty());
		}

		//
		// Reset just completed as we start a new event and make available the old one
		ResetBoolArray(m_aJustCompletedEvents);
		m_pPreviousEvent->Reset();
		
		//
		// Update current event index and remove the chosen one from the available ones
		m_pCurrentEvent = m_apEvents[eEventType];
		m_aAvailableEvents[m_pCurrentEvent->GetType()] = false;

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
		m_pPreviousEvent->Reset();
		
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
	if (shNULL != pListener)
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
 * @brief PollNewEvents
 */
void Player2EventManager::PollNewEvents(float dt)
{
	//
	// Event TypeWord always accessible
	if (!m_aAvailableEvents[e_player2_event_type_type_words])
	{
		m_aAvailableEvents[e_player2_event_type_type_words] = true;
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
	// TODO
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
		m_pCurrentEvent->Update(dt);
		if (m_pCurrentEvent->IsFinished())
		{
			//
			// Notify listeners on event finished
			m_pPlayer2EventListener->OnEventTypeFinished(m_pCurrentEvent);
		}
	}

	//
	// Handle user choice
	HandleUserChoice();

	//
	// Check typo jauge
	CheckTypoGaugeCompletion();
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
			m_pPlayer2EventListener->OnEventTypeCanceled(m_pPreviousEvent->GetType());
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
			// Notify listeners the EventType has changed
			m_pPlayer2EventListener->OnEventTypeChanged(m_pPreviousEvent, m_pCurrentEvent);
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
	m_pPlayer2EventListener->OnTypoGaugeUpdated(m_fTypoGaugeValue / m_fTypoGaugeMax);
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
		m_pPlayer2EventListener->OnTypoGaugeFilled();

		//
		// Reset typo gauge
		m_fTypoGaugeValue = 0.0f;
	}
}
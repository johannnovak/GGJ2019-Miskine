#pragma once

#include "ShSDK/ShSDK.h"

#include "Player2EventTypeWords.h"
//#include "Player2EventBoostTower.h"
//#include "Player2EventGrantSpecialAttack.h"
//#include "Player2EventControlEnemy.h"
//#include "Player2EventImmediateQTE.h"
//#inlcude "Player2EventSuperMegaCombo.h"

#include "IPlayer2EventListener.h"

#define TYPO_GAUGE_DEFAULT_MAX_VALUE 100.0f

class Player2EventManager
{
public:
	const Player2EventManager &			GetInstance					(void);

public:

	void								Initialize					(void);
	void								Release						(void);



	void								Update						(float dt);

	//
	// Event related
	bool								IsEventAvailable			(EPlayer2EventType eEventType);
	bool								IsEventJustCompleted		(EPlayer2EventType eEventType);
	Player2Event *						GetCurrentEvent				(void);

	bool								ChooseEventType				(EPlayer2EventType eEventType);
	bool								LeaveEventType				(void);

	bool								RegisterListener			(IPlayer2EventListener * pListener);
	bool								UnregisterListener			(IPlayer2EventListener * pListener);
protected:
private:
	void								SetEventTypeAvailable		(EPlayer2EventType eType);
	void								SetEventTypeUnavailable		(EPlayer2EventType eType);

	void								PollNewEvents				(float dt);
	void								OnCurrentEventFinished		(void);

	void								ResetBoolArray				(bool * aBool);
	void								HandleUserChoice			(void);

	void								IncreaseTypoGauge			(EPlayer2EventDifficulty eDifficulty);
	void								CheckTypoGaugeCompletion	(void);
public:
protected:
private:
	static Player2EventManager			s_Player2EventManager;

	ShUser *							m_pUser;

	Player2Event *						m_apEvents[e_player2_event_type_count];
	Player2EventTypeWords				m_eventTypeWords;
	//Player2EventBoostTower			m_eventBoostTower;
	//Player2EventGrantSpecialAttack	m_eventGrantSpecialAttack;
	//Player2EventControlEnemy			m_eventControlEnemy;
	//Player2EventImmediateQTE			m_eventControlImmediateQTE;
	//Player2EventSuperMegaCombo		m_eventControlSuperMegaCombo;

	bool								m_aAvailableEvents[e_player2_event_type_count];
	bool								m_aJustCompletedEvents[e_player2_event_type_count];
	Player2Event *						m_pCurrentEvent;
	Player2Event *						m_pPreviousEvent;

	float								m_fTypoGaugeValue;
	float								m_fTypoGaugeMax;

	//
	// Listener
	IPlayer2EventListener *				m_pPlayer2EventListener;
};


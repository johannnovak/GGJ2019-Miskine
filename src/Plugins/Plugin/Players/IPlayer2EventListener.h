#pragma once

#include "Player2Event.h"
#include "Player2EventTypeWords.h"
//#include "Player2EventBoostTower.h"
//#include "Player2EventGrantSpecialAttack.h"
//#include "Player2EventControlEnemy.h"
//#include "Player2EventImmediateQTE.h"
//#inlcude "Player2EventSuperMegaCombo.h"

class IPlayer2EventListener
{
public:
	//
	// To change bottom menu
	virtual void		OnEventTypeChanged					(Player2Event * pOldEvent, Player2Event * pNewEvent) = 0; 
	virtual void		OnEventTypeFinished					(Player2Event * pEvent) = 0;
	virtual void		OnEventTypeCanceled					(EPlayer2EventType eEventType) = 0;
	
	//
	// To update Gauge
	virtual void		OnTypoGaugeUpdated					(float fNormedValue) = 0; // [0, 1]
	virtual void		OnTypoGaugeFilled					(void) = 0;
	virtual void		OnTypoGaugeEmptied					(void) = 0;

	//
	// Specific EventType callbacks

	//
	// TypeWord
	virtual void		OnEventTypeTypeWordCharacterOK		(int iCharacterIndexOK) = 0;
	virtual void		OnEventTypeTypeWordCharacterNOK		(int iCharacterIndexNOK) = 0;

};

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
	// To notify available EventTypes
	virtual void		OnEventTypeAvailable				(Player2Event * pEvent) = 0;
	virtual void		OnEventTypeUnavailable				(Player2Event * pEvent) = 0;

	//
	// To change bottom menu
	virtual void		OnEventTypeBegin					(Player2Event * pEvent) = 0; 
	virtual void		OnEventTypeEnd						(Player2Event * pEvent) = 0; 
	virtual void		OnEventTypeFinished					(Player2Event * pEvent) = 0;
	
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

	//
	// Rewards
	virtual void		OnEventTypeRewardUserPireCoin			(int iPeerCoinAmount) = 0;
	virtual void		OnEventTypeRewardUserHP					(int iHPBonus) = 0;
	virtual void		OnEventTypeRewardGameSlowMotion			(float fSlowMotionFactor, float fDurationTime) = 0;
	virtual void		OnEventTypeRewardTowerAttack			(int iBonusValue, float fDurationTime) = 0;
	virtual void		OnEventTypeRewardTowerAttackSpeed		(int iBonusValue, float fDurationTime) = 0;
	virtual void		OnEventTypeRewardTowerRadius			(int iBonusValue, float fDurationTime) = 0;
	virtual void		OnEventTypeRewardTowerAttackAOE			(int iBonusValue, float fDurationTime) = 0;

	//
	// Malus
	virtual void		OnEventTypeMalusUserHP					(int iHPMalus) = 0;
	virtual void		OnEventTypeMalusGameFastForward			(float iFastForwardFactor, float fDurationTime) = 0;
	virtual void		OnEventTypeMalusGameNewEnemy			(int iEnemyCount) = 0;
	virtual void		OnEventTypeMalusGameNewWave				(int iWaveCount) = 0;
	virtual void		OnEventTypeMalusTowerAttack				(int iMalusValue, float fDurationTime) = 0;
	virtual void		OnEventTypeMalusTowerAttackSpeed		(int iMalusValue, float fDurationTime) = 0;
	virtual void		OnEventTypeMalusTowerRadius				(int iMalusValue, float fDurationTime) = 0;
	virtual void		OnEventTypeMalusTowerAttackAOE			(int iMalusValue, float fDurationTime) = 0;
};


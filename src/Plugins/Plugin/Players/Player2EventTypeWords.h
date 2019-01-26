#pragma once

#include "ShSDK/ShSDK.h"

#include "Player2Event.h"

class Player2EventTypeWords : public Player2Event
{
public:
	explicit					Player2EventTypeWords	(void);
	explicit					Player2EventTypeWords	(const CShWString & strWordToType);
	virtual						~Player2EventTypeWords	(void);
	
	virtual void				Initialize				(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void				Release					(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void				Update					(float dt, ShGUIControlEditBox * pEditBoxHidden) SH_ATTRIBUTE_OVERRIDE;
	
	virtual EPlayer2EventType	GetType					(void) SH_ATTRIBUTE_OVERRIDE;
	
	void						SetWordToType			(const CShWString & wstrWordToType);
protected:
	virtual void				ResetInternal			(void) SH_ATTRIBUTE_OVERRIDE;
private:
	static void					SerializeDictionnary	(void);

public:
	ShUser *					m_pUser;

	CShWString					m_wstrWordToType;
	int							m_iCurrentIndex;

	static CShArrayMap<EPlayer2EventDifficulty, CShArray<CShWString> >	s_aawstrDictionnary;
};
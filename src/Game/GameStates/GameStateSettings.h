#ifndef GAMESTATESETTINGS_H
#define GAMESTATESETTINGS_H

#include "GameState.h"
#include <ShSDK/ShSDK.h>

class GameStateSettings : public GameState
{
public:
	explicit			GameStateSettings		(void);
	virtual				~GameStateSettings		(void) override;

	void				init					(void) override;
	void				release					(void) override;

	void				entered					(void) override;
	void				exiting					(void) override;

	void				obscuring				(void) override;
	void				revealed				(void) override;

	void				update					(float dt) override;

	void				touchBegin				(const CShVector2 & pos, float ratio) override;
	void				touchEnd				(const CShVector2 & pos, float ratio) override;
	void				touchMove				(const CShVector2 & pos, float ratio) override;
protected:
private:
//	void


public:
protected:
private:
	ShGUIControlPanel *	m_pMainPanel;
};

#endif // GAMESTATESETTINGS_H

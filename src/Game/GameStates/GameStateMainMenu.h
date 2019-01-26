#pragma once

#include "GameState.h"
#include <ShSDK/ShSDK.h>

class GameStateMainMenu : public GameState
{

public:

	explicit			GameStateMainMenu		(void);
	virtual				~GameStateMainMenu		(void) override;

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

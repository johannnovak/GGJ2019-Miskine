#ifndef GAMESTATECREDITS_H
#define GAMESTATECREDITS_H

#include "GameState.h"
#include <ShSDK/ShSDK.h>


class GameStateCredits : public GameState
{
public:
public:
	explicit			GameStateCredits		(void);
	virtual				~GameStateCredits		(void) override;

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

public:
protected:
private:
	ShGUIControlPanel *	m_pMainPanel;
};

#endif // GAMESTATECREDITS_H

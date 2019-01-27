#ifndef GAMESTATEGAMEOVER_H
#define GAMESTATEGAMEOVER_H

#include "GameState.h"
#include <ShSDK/ShSDK.h>


class GameStateGameOver : public GameState
{
public:
	explicit			GameStateGameOver		(void);
	virtual				~GameStateGameOver		(void) override;

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
	static bool			ButtonOkClicked			(ShGUIControl * pControl, const CShVector2 & vPosition);

public:
protected:
private:
	ShGUIControlPanel *	m_pMainPanel;
};

#endif // GAMESTATEGAMEOVER_H

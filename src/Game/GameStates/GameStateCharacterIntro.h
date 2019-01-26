#ifndef GAMESTATECHARACTERINTRO_H
#define GAMESTATECHARACTERINTRO_H

#include "GameState.h"
#include <ShSDK/ShSDK.h>

class GameStateCharacterIntro : public GameState
{
public:
	explicit	GameStateCharacterIntro		(void);
	virtual		~GameStateCharacterIntro	(void) override;

	void		init						(void) override;
	void		release						(void) override;

	void		entered						(void) override;
	void		exiting						(void) override;

	void		obscuring					(void) override;
	void		revealed					(void) override;

	void		update						(float dt) override;

	void		touchBegin					(const CShVector2 & pos, float ratio) override;
	void		touchEnd					(const CShVector2 & pos, float ratio) override;
	void		touchMove					(const CShVector2 & pos, float ratio) override;
protected:
private:
//	void


public:
protected:
private:
	ShGUIControlPanel *	m_pMainPanel;
};

#endif // GAMESTATECHARACTERINTRO_H

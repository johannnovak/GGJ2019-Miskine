#pragma once

class CShVector2;

class GameState
{

protected:

	explicit GameState(void);
	virtual ~GameState(void);

public:

	virtual void init		(void) = 0;
	virtual void release	(void) = 0;

	virtual void entered	(void) = 0;
	virtual void exiting	(void) = 0;

	virtual void obscuring	(void) = 0;
	virtual void revealed	(void) = 0;

	virtual void update		(float dt) = 0;

	virtual void touchBegin	(const CShVector2 & pos, float ratio);
	virtual void touchEnd	(const CShVector2 & pos, float ratio);
	virtual void touchMove	(const CShVector2 & pos, float ratio);

};

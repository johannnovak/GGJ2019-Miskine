#pragma once

class TowerBase
{
public:

	explicit	 TowerBase		(void);
	virtual		~TowerBase		(void);

	void		Initialize		(void);
	void		Release			(void);

	void		Update			(float dt);

private:

	
};


#pragma once

#include "ShSDK/ShSDK.h"


class WaveManager
{
public:

	explicit	 WaveManager		(void);
	virtual		~WaveManager		(void);

	void		Initialize			(void);
	void		Release				(void);

	void		Update				(float dt);
private:

};


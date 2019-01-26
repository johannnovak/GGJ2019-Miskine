#pragma once

#include "ShSDK/ShSDK.h"

class Wave
{

public:

	explicit	 Wave				(void);
	virtual		~Wave				(void);

	void		Initialize			(void);
	void		Release				(void);

	void		Start				(void);
	void		Stop				(void);

	void		Update				(float dt);
private:

public:

private:

};


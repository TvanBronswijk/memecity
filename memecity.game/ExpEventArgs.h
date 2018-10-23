#pragma once
#include <EventArgs.h>
class ExpEventArgs :
	public EventArgs
	
{
public:
	int exp;
	ExpEventArgs();
	~ExpEventArgs();
};


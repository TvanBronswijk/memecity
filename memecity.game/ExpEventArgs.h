#ifndef _EXP_EVENT_ARGS_H
#define _EXP_EVENT_ARGS_H
#include <EventArgs.h>
struct ExpEventArgs :
	public EventArgs
	
{
public:
	int exp;
	ExpEventArgs();
	~ExpEventArgs();
};

#endif


#ifndef _TIMERFACADE_H
#define _TIMERFACADE_H
#include <SDL.h>

class TimerFacade
{

private:
	unsigned int startTicks;
	unsigned int elaspsedTicks;
	float deltaTime;

public:

	void Reset();
	float DeltaTime();

	void Update();

	TimerFacade();
};

#endif

#ifndef _TIMERFACADE_H
#define _TIMERFACADE_H
#include <SDL.h>

class TimerFacade
{

private:
	static TimerFacade* instance;

	unsigned int startTicks;
	unsigned int elaspsedTicks;
	float deltaTime;

public:
	static TimerFacade* GetInstance();
	static void Release();

	void Reset();
	float DeltaTime();

	void Update();

private:
	TimerFacade();
	~TimerFacade();
};

#endif

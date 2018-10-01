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
	float timeScale;

public:
	static TimerFacade* GetInstance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:
	TimerFacade();
	~TimerFacade();
};

#endif

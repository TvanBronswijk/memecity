#include "TimerFacade.h"
#include <SDL.h>

TimerFacade* TimerFacade::instance = nullptr;

TimerFacade* TimerFacade::GetInstance()
{
	if (instance == nullptr)
		instance = new TimerFacade();

	return instance;
}

void TimerFacade::Release()
{
	delete instance;
	instance = nullptr;
}

TimerFacade::TimerFacade()
{
	Reset();
	timeScale = 1.0f;
}

TimerFacade::~TimerFacade()
{

}

void TimerFacade::Reset()
{
	startTicks = SDL_GetTicks();
	elaspsedTicks = 0;
	deltaTime = 0.0f;
}

float TimerFacade::DeltaTime()
{
	return deltaTime;
}

void TimerFacade::TimeScale(float t)
{
	timeScale = t;
}


float TimerFacade::TimeScale()
{
	return timeScale;
}

void TimerFacade::Update()
{
	elaspsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elaspsedTicks * 0.001f;
}
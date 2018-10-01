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

void TimerFacade::Update()
{
	elaspsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elaspsedTicks * 0.001f;
}
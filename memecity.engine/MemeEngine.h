#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H

#include "InputManager.h"
#include "MultimediaManager.h"

class TimerFacade;

class MemeEngine
{
protected:
	MultimediaManager multimedia_manager{ false };
	InputManager input_manager{};
	std::unique_ptr<TimerFacade> timer;

	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

public:
	int run();
	MemeEngine();
};

#endif

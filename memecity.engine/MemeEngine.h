#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H

#include <memory>
#include "MultimediaManager.h"
#include "InputManager.h"
#include "TimerFacade.h"

class MemeEngine
{
protected:
	std::shared_ptr<MultimediaManager> multimedia_manager;
	std::shared_ptr<InputManager> input_manager;
	std::shared_ptr<TimerFacade> timer;

	virtual bool init() = 0;
	virtual void handle() = 0;

public:
	int run();
	MemeEngine();
};

#endif
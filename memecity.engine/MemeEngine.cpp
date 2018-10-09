#include "MemeEngine.h"

MemeEngine::MemeEngine()
{

	multimedia_manager = std::make_shared<MultimediaManager>(false);
	input_manager = std::make_unique<InputManager>();
	timer = std::make_unique<TimerFacade>();
}


int MemeEngine::Run()
{
	if (Init()) {
		while (!input_manager->is_quit_pressed())
		{
			Handle();
		}
		return 0;
	}
	return 1;
}




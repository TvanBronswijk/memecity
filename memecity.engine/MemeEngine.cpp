#include "MemeEngine.h"

MemeEngine::MemeEngine()
{
	timer = std::make_unique<TimerFacade>();
}

int MemeEngine::run()
{
	if (multimedia_manager.init()) {
		init();
		while (!input_manager.is_quit_pressed())
		{
			timer->update();
			if (timer->get_delta_time() >= 1.0f / 60)
			{
				input_manager.update();
				handle();
				timer->reset();
			}
		}
		return 0;
	}
	return 1;
}

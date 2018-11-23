#include "MemeEngine.h"
#include "Engine\SDL\TimerFacade.h"

namespace memecity::engine {
	MemeEngine::MemeEngine()
	{
	}

	int MemeEngine::run()
	{
		if (multimedia_manager.init()) {
			init();
			while (!input_manager.is_quit_pressed())
			{
				timer.update();
				update(timer.get_delta_time());
				input_manager.update();
				
				if (timer.get_delta_time() >= 1.0f / 60)
				{	
					multimedia_manager.clear_graphics();
					draw();
					multimedia_manager.render_graphics();
					timer.reset();
				}
			}
			return 0;
		}
		return 1;
	}
}

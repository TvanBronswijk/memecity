#include "MemeEngine.h"
#include <iostream>
#include <thread>
#include "Engine\SDL\TimerFacade.h"

namespace memecity::engine {
	MemeEngine::MemeEngine()
	{
	}

	int MemeEngine::run()
	{
		if (multimedia_manager.init()) {
			init();
			
			std::thread logic([&]() {
				while (!input_manager.is_quit_pressed())
				{
					update(timer.get_delta_time());
				}
			});
			
			std::thread ui([&]() {
				while (!input_manager.is_quit_pressed())
				{
						multimedia_manager.clear_graphics();
						draw();
						multimedia_manager.render_graphics();
				}
			});
#ifdef DEBUG
			std::cout << "threads spawned\n";
#endif
			while (!input_manager.is_quit_pressed())
			{
				timer.update();
				input_manager.update();
			};


			logic.join();
			ui.join();
			return 0;
		}
		return 1;
	}
}

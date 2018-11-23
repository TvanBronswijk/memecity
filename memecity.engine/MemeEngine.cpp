#include "MemeEngine.h"
#include <iostream>
#include <thread>
#include "Engine\SDL\TimerFacade.h"

namespace memecity::engine {
	
	MemeEngine::MemeEngine()
	{
	}

	int MemeEngine::run_multi()
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
					if (timer.get_delta_time() >= 1.0f / 60.0f) {
						multimedia_manager.clear_graphics();
						draw();
						multimedia_manager.render_graphics();
						timer.reset();
					}
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

	int MemeEngine::run_single()
	{
		if (multimedia_manager.init()) {
			init();
			while (!input_manager.is_quit_pressed())
			{
				timer.update();
				input_manager.update();
				update(timer.get_delta_time());
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

	int MemeEngine::run(Threading flag)
	{
		switch (flag) {
		case Threading::multithreaded:
			return run_multi();
		case Threading::singlethreaded:
			return run_single();
		}
	}
}

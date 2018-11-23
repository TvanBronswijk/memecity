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

	int MemeEngine::run_single()
	{

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

	int MemeEngine::run(Threading flag)
	{
		if (multimedia_manager.init()) {
			init();
			switch (flag) {
			case Threading::multithreaded:
				set_runnable([&]() { return run_multi(); });
			case Threading::singlethreaded:
				set_runnable([&]() { return run_single(); });
			}
			return _runnable();
		}
		return 0;
	}
}

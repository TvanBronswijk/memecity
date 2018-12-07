#include "MemeEngine.h"
#include <iostream>
#include <thread>
#include "Engine\SDL\TimerFacade.h"

namespace memecity::engine {
	int multithreaded(MemeEngine& engine)
	{
#ifdef DEBUG
		std::cout << "multithreaded\n"
			<< "main thread: " << std::this_thread::get_id() << '\n';
#endif
		std::thread logic([&]() {
#ifdef DEBUG
			std::cout << "	logic thread: " << std::this_thread::get_id() << '\n';
#endif
			while (!engine.input_manager.is_quit_pressed()) {
				engine.update(engine.timer.get_delta_time());
			}
		});
		while (!engine.input_manager.is_quit_pressed()) {
			engine.timer.update();
			engine.input_manager.update();
			if (engine.timer.get_delta_time() >= 1.0f / 60.0f) {
				if (engine.get_fps_trigger) {
					engine.fps = 1.0f / engine.timer.get_delta_time();
					engine.get_fps_trigger = false;
				}
				engine.multimedia_manager.clear_graphics();
				engine.draw();
				engine.multimedia_manager.render_graphics();
				engine.timer.reset();
			}
		};
		logic.join();
		return 0;
	}

	int singlethreaded(MemeEngine& engine)
	{
#ifdef DEBUG
		std::cout << "singlethreaded\n";
#endif
		while (!engine.input_manager.is_quit_pressed()) {
			engine.timer.update();
			engine.input_manager.update();
			engine.update(engine.timer.get_delta_time());
			if (engine.timer.get_delta_time() >= 1.0f / 60.0f) {
				engine.multimedia_manager.clear_graphics();
				engine.draw();
				engine.multimedia_manager.render_graphics();
				engine.timer.reset();
			}
		}
		return 0;
	}

	int MemeEngine::run(Threading flag)
	{
		if (multimedia_manager.init()) {
			init();
			set_runnable(flag);
			return _runnable(*this);
		}
		return 1;
	}
	int MemeEngine::run(Runnable<int> runnable)
	{
		if (multimedia_manager.init()) {
			init();
			set_runnable(runnable);
			return _runnable(*this);
		}
		return 1;
	}
	void MemeEngine::set_runnable(Threading flag)
	{
		switch (flag) {
		case Threading::multithreaded:
			set_runnable(multithreaded);
			break;
		case Threading::singlethreaded:
			set_runnable(singlethreaded);
			break;
		}
	}
	void MemeEngine::set_runnable(Runnable<int> runnable)
	{
		_runnable = runnable;
	}
}

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
			sdl::TimerFacade bleh;
			float prev = 0.0f;
			while (!engine.input_manager.is_quit_pressed()) {
				prev = bleh.get_delta_time();
				bleh.update();
			//	std::this_thread::sleep_for(std::chrono::seconds(1));

				engine.update(bleh.get_delta_time() - prev);
				//std::cout << "Update" << bleh.get_delta_time() - prev <<"\n" ;

			//	bleh.reset();
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
				//std::cout << "Draw" << engine.timer.get_delta_time() << "\n";

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

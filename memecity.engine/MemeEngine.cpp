#include "MemeEngine.h"
#include <iostream>
#include <thread>
#include "Engine\SDL\TimerFacade.h"


int multithreaded(memecity::engine::MemeEngine& engine)
{
#ifdef DEBUG
	std::cout << "multithreaded\n"
		<< "main thread: " << std::this_thread::get_id() << '\n';
#endif
	std::thread logic([&]() {
#ifdef DEBUG
		std::cout << "	logic thread: " << std::this_thread::get_id() << '\n';
#endif
		while (!engine.get_input_manager().is_quit_pressed()) {
			engine.update(engine.get_timer().get_delta_time());
		}
	});

	std::thread ui([&]() {
#ifdef DEBUG
		std::cout << "	ui thread: " << std::this_thread::get_id() << '\n';
#endif
		while (!engine.get_input_manager().is_quit_pressed()) {
			if (engine.get_timer().get_delta_time() >= 1.0f / 60.0f) {
				engine.get_multimedia_manager().clear_graphics();
				engine.draw();
				engine.get_multimedia_manager().render_graphics();
				engine.get_timer().reset();
			}
		}
	});
	while (!engine.get_input_manager().is_quit_pressed()) {
		engine.get_timer().update();
		engine.get_input_manager().update();
	};


	logic.join();
	ui.join();
	return 0;
}

int singlethreaded(memecity::engine::MemeEngine& engine)
{

#ifdef DEBUG
	std::cout << "singlethreaded\n";
#endif
	while (!engine.get_input_manager().is_quit_pressed()) {
		engine.get_timer().update();
		engine.get_input_manager().update();
		engine.update(engine.get_timer().get_delta_time());
		if (engine.get_timer().get_delta_time() >= 1.0f / 60.0f) {
			engine.get_multimedia_manager().clear_graphics();
			engine.draw();
			engine.get_multimedia_manager().render_graphics();
			engine.get_timer().reset();
		}
	}
	return 0;
}

namespace memecity::engine {
	int MemeEngine::run(Threading flag)
	{
		if (multimedia_manager.init()) {
			init();
			set_runnable(flag);
			return _runnable(*this);
		}
		return 0;
	}
	int MemeEngine::run(Runnable<int> runnable)
	{
		if (multimedia_manager.init()) {
			init();
			set_runnable(runnable);
			return _runnable(*this);
		}
		return 0;
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

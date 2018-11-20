#include "MemeEngine.h"
#include "Engine\SDL\TimerFacade.h"

namespace memecity::engine {
	MemeEngine::MemeEngine()
	{
		auto boundary = BoundaryRectangle(0, 0, 1356, 1356);
		auto &test = boundary;
		_quad_tree = QuadTree(4, test);
		timer = std::make_unique<sdl::TimerFacade>();
	}

	int MemeEngine::run()
	{
		if (multimedia_manager.init()) {
			init();
			while (!input_manager.is_quit_pressed())
			{
				timer->update();
				update(timer->get_delta_time());
				if (timer->get_delta_time() >= 1.0f / 60)
				{
					input_manager.update();
					multimedia_manager.clear_graphics();
					draw();
					multimedia_manager.render_graphics();
					_quad_tree.update();
					timer->reset();
				}
			}
			return 0;
		}
		return 1;
	}
}

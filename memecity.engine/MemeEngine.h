#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H

#include "Engine\InputManager.h"
#include "Engine\MultimediaManager.h"
#include "Engine\StorageManager.h"
#include "QuadTree.h"

namespace memecity::engine {
	namespace sdl {
		class TimerFacade;
	};

	class MemeEngine
	{
	protected:
		QuadTree _quad_tree;
		StorageManager storage_manager;
		MultimediaManager multimedia_manager{ false };
		InputManager input_manager{};
		std::unique_ptr<sdl::TimerFacade> timer;

		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;

	public:
		int run();
		MemeEngine();
	};
}

#endif
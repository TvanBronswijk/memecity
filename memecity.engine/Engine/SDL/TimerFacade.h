﻿#ifndef _TIMERFACADE_H
#define _TIMERFACADE_H

#include <SDL.h>

namespace memecity::engine::sdl {
	class TimerFacade
	{
	private:
		unsigned int start_ticks{};
		unsigned int elapsed_ticks{};
		float delta_time{};

	public:
		TimerFacade();

		///<summary>Resets the elapsed ticks.</summary>
		void reset();

		///<summary>Returns the current delta time.</summary>
		float get_delta_time() const;

		///<summary>Sets delta time to elapsed time since last update.</summary>
		void update();
	};
}

#endif

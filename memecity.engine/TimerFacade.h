#ifndef _TIMERFACADE_H
#define _TIMERFACADE_H
#include <SDL.h>

class TimerFacade
{
private:
	unsigned int start_ticks{};
	unsigned int elapsed_ticks{};
	float delta_time{};

public:
	TimerFacade();
	void reset();
	float get_delta_time() const;
	void update();
};

#endif

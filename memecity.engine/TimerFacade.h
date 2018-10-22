#ifndef _TIMERFACADE_H
#define _TIMERFACADE_H

#include <SDL.h>
#include "Updatable.h"

class TimerFacade : public Updatable
{
private:
	unsigned int start_ticks{};
	unsigned int elapsed_ticks{};
	float delta_time{};

public:
	TimerFacade();
	void reset();
	float get_delta_time() const;
	void update() override;
};

#endif

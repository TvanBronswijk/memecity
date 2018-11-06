#ifndef _ANIMATED_TEXTURE_H
#define _ANIMATED_TEXTURE_H

#include "Texture.h"
#include "TimerFacade.h"
#include <iostream>

class AnimatedTexture : public Texture, public Updatable
{
public:
	enum class AnimationDirection { horizontal, vertical };
	enum class Direction { down, left, up, right, idle };

private:
	TimerFacade* timer_facade;
	AnimationDirection animation_direction;
	Direction direction;

	int start_x;
	int start_y;
	
	int frame_count;
	
	float animation_timer;
	float animation_speed;
	
	float time_per_frame;

public:	
	AnimatedTexture(TimerFacade* timer_facade, std::string filename, int x, int y, int w, int h, int frame_count, float animation_speed, AnimationDirection direction);
	~AnimatedTexture();
	void set_direction(Direction direction);
	void update() override;
};

#endif
#ifndef _ANIMATED_TEXTURE_H
#define _ANIMATED_TEXTURE_H

#include "Texture.h"
#include "TimerFacade.h"

class AnimatedTexture : public Texture, public Updatable
{
public:
	enum ANIMATION_DIRECTION { horizontal = 0, vertical = 1};
	enum WALKING_DIRECTION { down = 0, left = 1, up = 2, right = 3 };
	
	AnimatedTexture(TimerFacade* timer_facade, std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture, int x, int y, int w, int h, int frame_count, float animation_speed, ANIMATION_DIRECTION direction);
	~AnimatedTexture();
	void set_walking_direction(WALKING_DIRECTION direction);
	void update() override;

private:
	TimerFacade* timer_facade;
	Vector2 previous_position;
	ANIMATION_DIRECTION animation_direction;
	WALKING_DIRECTION walking_direction;

	int start_x;
	int start_y;
	int frame_count;

	float animation_timer;
	float animation_speed;
	float time_per_frame;

	bool is_walking = false;

	void idle();
};

#endif
#ifndef _ANIMATED_TEXTURE_H
#define _ANIMATED_TEXTURE_H
#include "Texture.h"
#include "TimerFacade.h"

class AnimatedTexture : public Texture
{
	public:
		enum WRAP_MODE { once = 0, loop = 1 };
		enum ANIMATION_DIRECTION { horizontal = 0, vertical = 1};
		AnimatedTexture(SDL_Texture texture, int x, int y, int w, int h, int frame_count, float animation_speed, ANIMATION_DIRECTION direction);
		~AnimatedTexture();
		void set_wrap_mode(WRAP_MODE mode);
		void update();

	private:
		TimerFacade* timer_facade;

		int start_x;
		int start_y;

		float animation_timer;
		float animation_speed;
		float time_per_frame;

		int frame_count;
		WRAP_MODE wrap_mode;
		ANIMATION_DIRECTION animation_direction;
		bool animation_is_done;
};

#endif
#ifndef _ANIMATED_TEXTURE_H
#define _ANIMATED_TEXTURE_H

#include "..\SDL\TimerFacade.h"
#include "Texture.h"
#include <string>

namespace memecity::engine::texture {
	class AnimatedTexture : public Texture
	{
	public:
		enum class AnimationDirection { horizontal, vertical };
		enum class Direction { down, left, up, right, idle };

	private:
		sdl::TimerFacade &timer_facade;
		AnimationDirection animation_direction;
		Direction direction;

		int start_x;
		int start_y;

		int frame_count;

		float animation_timer;
		float animation_speed;

		float time_per_frame;

	public:
		AnimatedTexture(sdl::TimerFacade &timer_facade, std::string filename, int x, int y, const int w, const int h, const int frame_count, const float animation_speed, const AnimationDirection direction)
			: Texture(filename, x, y, w, h), timer_facade(timer_facade), animation_direction(direction), start_x(x), start_y(y), frame_count(frame_count), animation_speed(animation_speed), time_per_frame(animation_speed / frame_count), direction(Direction::down), animation_timer(0.0f)
		{};
		~AnimatedTexture() = default;
		void set_direction(Direction direction);
		void update();
	};
}

#endif

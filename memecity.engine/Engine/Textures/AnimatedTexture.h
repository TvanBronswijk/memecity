#ifndef _ANIMATED_TEXTURE_H
#define _ANIMATED_TEXTURE_H

#include "Texture.h"
#include <string>

namespace memecity::engine::texture 
{ 
	class AnimatedTexture : public Texture
	{
	public:
		enum class AnimationDirection { horizontal, vertical };
		enum class AnimationState { walk_down, walk_left, walk_up, walk_right, idle, dying };

	private:
		AnimationDirection _animation_direction;
		AnimationState _current_state;

		int _start_x;
		int _start_y;
		int _frame_count;

		float _animation_timer;
		float _animation_speed;
		float _time_per_frame;

	public:
		AnimatedTexture(std::string filename, int x, int y, const int w, const int h, const int frame_count, const float animation_speed, const AnimationDirection direction)
			: Texture(filename, x, y, w, h), _animation_direction(direction), _current_state(AnimationState::idle), _start_x(x), _start_y(y), _frame_count(frame_count), _animation_timer(0.0f), _animation_speed(animation_speed), _time_per_frame(animation_speed / frame_count)
		{};
		~AnimatedTexture() = default;

		void set_state(AnimationState state);
		void set_animation_direction(AnimationDirection direction);
		const AnimationDirection& get_animation_direction() const;
		const AnimationState& get_state() const;

		void update(float dt);
	};
}

#endif

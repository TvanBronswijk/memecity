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
		enum class AnimationState { down, left, up, right, idle };

	private:
		AnimationDirection _animation_direction;
		AnimationState _current_state;

		float _start_x;
		float _start_y;
		float _frame_count;

		float _animation_timer;
		float _animation_speed;
		float _time_per_frame;

	public:
		AnimatedTexture(std::string filename, float start_x, float start_y, const float w, const float h, const int frame_count, const float animation_speed, const AnimationDirection direction)
			: Texture(filename, start_x, start_y, w, h), _animation_direction(direction), _current_state(AnimationState::idle), _start_x(start_x), _start_y(start_y), _frame_count(frame_count), _animation_timer(0.0f), _animation_speed(animation_speed), _time_per_frame(animation_speed / frame_count)
		{}

		~AnimatedTexture() = default;

		void row(float y);
		float row() const;

		void column(float x);
		float column() const;

		bool is_last() const;

		void set_state(AnimationState state);
		void set_animation_direction(AnimationDirection direction);
		const AnimationDirection& get_animation_direction() const;
		const AnimationState& get_state() const;

		void update(float dt);
	};
}

#endif

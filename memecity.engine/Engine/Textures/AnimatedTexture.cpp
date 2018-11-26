#include "AnimatedTexture.h"

namespace memecity::engine::texture {

	void AnimatedTexture::set_state(AnimationState state)
	{
		this->_current_state = state;
		this->_start_x = static_cast<int>(state) * texture_width;
	}

	void AnimatedTexture::set_animation_direction(AnimationDirection direction)
	{
		this->_animation_direction = direction;
	}

	const AnimatedTexture::AnimationDirection& AnimatedTexture::get_animation_direction() const
	{
		return this->_animation_direction;
	}

	const AnimatedTexture::AnimationState& AnimatedTexture::get_state() const
	{
		return this->_current_state;
	}

	void AnimatedTexture::update()
	{
		_animation_timer += _timer_facade.get_delta_time();
		
		if (_animation_timer >= _animation_speed)
		{
			_animation_timer -= _animation_speed;
		}

		if (_current_state == AnimationState::dying)
		{
			if (clipped_rect.x != 3 * texture_width)
			{
				clipped_rect.y = 5 * texture_width;
				clipped_rect.x = int(_animation_timer / _time_per_frame) * texture_width;
			}
		}
		else if (_current_state != AnimationState::idle && _animation_direction == AnimationDirection::vertical)
		{
			clipped_rect.x = _start_x;
			clipped_rect.y = _start_y + int(_animation_timer / _time_per_frame) * texture_height;
		}
		else if (_animation_direction == AnimationDirection::horizontal)
		{
			clipped_rect.y = 4 * texture_width;
			clipped_rect.x = int(_animation_timer / _time_per_frame) * texture_width;
		}
		else
		{
			clipped_rect.y = _start_y;
		}
	}
}

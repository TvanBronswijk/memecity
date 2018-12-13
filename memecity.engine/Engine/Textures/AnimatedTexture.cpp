#include "AnimatedTexture.h"
#include <iostream>

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

	float AnimatedTexture::column() const
	{
		return clipped_rect.x / texture_width;
	}

	void AnimatedTexture::column(float x)
	{
		clipped_rect.x = x * texture_width;
	}

	void AnimatedTexture::row(float y)
	{
		clipped_rect.y = y * texture_height;
	}

	float AnimatedTexture::row() const
	{
		return clipped_rect.y / texture_height;
	}


	void AnimatedTexture::update(float dt)
	{
		_animation_timer += dt;
		
		if (_animation_timer >= _animation_speed)
		{
			_animation_timer -= _animation_speed;
		}

		if (_current_state != AnimationState::idle && _animation_direction == AnimationDirection::vertical)
		{
			clipped_rect.x = _start_x;
			clipped_rect.y = _start_y + int(_animation_timer / _time_per_frame) * texture_height;
		}
		else if (_animation_direction == AnimationDirection::horizontal)
		{
			clipped_rect.x = int(_animation_timer / _time_per_frame) * texture_width;
		}
		else
		{
			clipped_rect.y = _start_y;
		}
	}
}

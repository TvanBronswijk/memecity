#include "AnimatedTexture.h"

namespace memecity::engine::texture {
	
	void AnimatedTexture::set_state(AnimationState state)
	{
		this->_current_state = state;
		if (state == AnimationState::idle)
		{
			this->clipped_rect.x = 0;
		}
		else
		{
			this->clipped_rect.x = static_cast<int>(state) * texture_width;
		}
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

	int AnimatedTexture::column() const
	{
		return clipped_rect.x / texture_width;
	}

	bool AnimatedTexture::is_last() const
	{
		return row() == frame_count() - 1;
	}

	void AnimatedTexture::column(const float x)
	{
		clipped_rect.x = x * texture_width;
		_column_changed = true;
	}

	int AnimatedTexture::frame_count() const
	{
		return _frame_count;
	}

	void AnimatedTexture::row(const float y)
	{
		clipped_rect.y = y * texture_height;
		_row_changed = true;
	}

	int AnimatedTexture::row() const
	{
		return clipped_rect.y / texture_height;
	}

	void AnimatedTexture::update(const float dt)
	{
		_animation_timer += dt;
		if (_animation_timer >= _animation_speed)
		{
			_animation_timer -= _animation_speed;
		}

		if (_animation_direction == AnimationDirection::vertical)
		{
			if (_current_state == AnimationState::idle)
			{
				if (_column_changed)
				{
					if (!_row_changed)
					{
						clipped_rect.y = _start_y + int(_animation_timer / _time_per_frame) * texture_height;
					}

					_row_changed = false;
					_column_changed = false;
				}
				else
				{
					clipped_rect.y = 0;
				}
			}
			else
			{
				if (!_row_changed)
				{
					clipped_rect.y = _start_y + int(_animation_timer / _time_per_frame) * texture_height;
				}
			}
		}
		else if (_animation_direction == AnimationDirection::horizontal)
		{
			if (_current_state == AnimationState::idle)
			{
				if (_row_changed)
				{
					clipped_rect.x = _start_x + int(_animation_timer / _time_per_frame) * texture_width;
					_row_changed = false;
				}
				else
				{
					clipped_rect.x = 0;
				}
			}
			else
			{
				clipped_rect.x = _start_x + int(_animation_timer / _time_per_frame) * texture_width;
			}
		}
	}
}

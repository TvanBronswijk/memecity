#include "AnimatedTexture.h"

namespace memecity::engine::texture {

	void AnimatedTexture::set_direction(Direction direction)
	{
		this->direction = direction;
		this->start_x = static_cast<int>(direction) * texture_width;
	}

	void AnimatedTexture::set_animation_direction(const AnimationDirection direction)
	{
		this->animation_direction = direction;
	}

	AnimatedTexture::AnimationDirection AnimatedTexture::get_animation_direction() const
	{
		return this->animation_direction;
	}

	AnimatedTexture::Direction AnimatedTexture::get_direction() const
	{
		return this->direction;
	}

	void AnimatedTexture::update()
	{
		animation_timer += timer_facade.get_delta_time();
		if (animation_timer >= animation_speed)
		{
			animation_timer -= animation_speed;
		}

		if (direction != Direction::idle)
		{
			if (animation_direction == AnimationDirection::vertical)
			{
				clipped_rect.x = start_x;
				clipped_rect.y = start_y + int(animation_timer / time_per_frame) * texture_height;
			}
		}
		else if (animation_direction == AnimationDirection::horizontal)
		{
			const auto start_x_index = 0;
			clipped_rect.y = 4 * texture_width;
			clipped_rect.x = start_x_index + int(animation_timer / time_per_frame) * texture_width;
		}
		else
		{
			clipped_rect.y = 0;
		}
	}
}

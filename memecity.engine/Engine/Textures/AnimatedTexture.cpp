#include "AnimatedTexture.h"

namespace memecity::engine::texture {
	void AnimatedTexture::set_direction(Direction direction)
	{
		this->direction = direction;
		this->start_x = static_cast<int>(direction) * texture_width;
	}

	void AnimatedTexture::update()
	{
		if (direction != Direction::idle)
		{
			animation_timer += timer_facade.get_delta_time();
			if (animation_timer >= animation_speed)
			{
				animation_timer -= animation_speed;
			}
			if (animation_direction == AnimationDirection::horizontal)
			{
				clipped_rect.x = start_x + int(animation_timer / time_per_frame) * texture_width;
			}
			else
			{
				clipped_rect.x = start_x;
				clipped_rect.y = start_y + int(animation_timer / time_per_frame) * texture_height;
			}
		}
		else
		{
			clipped_rect.y = 0;
		}
	}
}

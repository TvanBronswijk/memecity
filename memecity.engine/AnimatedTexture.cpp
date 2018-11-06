#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(TimerFacade* timer_facade, std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture, int x, int y,
                                     const int w, const int h, const int frame_count, const float animation_speed, const AnimationDirection direction) : Texture(graphics_facade, texture, x, y, w, h)
{
	this->timer_facade = timer_facade;
	this->direction = Direction::down;

	start_x = x;
	start_y = y;

	this->frame_count = frame_count;
	this->animation_speed = animation_speed;
	time_per_frame = animation_speed / frame_count;
	animation_timer = 0.0f;
	animation_direction = direction;
}

AnimatedTexture::~AnimatedTexture() = default;

void AnimatedTexture::set_direction(const Direction direction)
{
	this->direction = direction;
	this->start_x = static_cast<int>(direction) * texture_width;
}

void AnimatedTexture::update()
{
	if (direction != Direction::idle)
	{
		animation_timer += timer_facade->get_delta_time();
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

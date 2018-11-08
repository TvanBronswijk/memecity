#include "AnimatedCharacter.h"

AnimatedCharacter::AnimatedCharacter(TimerFacade* timer_facade, std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture, int x, int y,
	int w, int h, int frame_count, float animation_speed, ANIMATION_DIRECTION direction) : Texture(graphics_facade, texture, x, y, w, h)
{
	this->timer_facade = timer_facade;
	this->walking_direction = down;

	start_x = x;
	start_y = y;

	this->frame_count = frame_count;
	this->animation_speed = animation_speed;
	time_per_frame = animation_speed / frame_count;
	animation_timer = 0.0f;
	animation_direction = direction;
}

AnimatedCharacter::~AnimatedCharacter() = default;

void AnimatedCharacter::set_walking_direction(WALKING_DIRECTION direction)
{
	this->walking_direction = direction;
	this->start_x = direction * texture_width;
}

void AnimatedCharacter::update()
{
	if (walking_direction != idle)
	{
		animation_timer += timer_facade->get_delta_time();
		if (animation_timer >= animation_speed)
		{
			animation_timer -= animation_speed;
		}
		if (animation_direction == horizontal)
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

	this->previous_position = get_position();
}


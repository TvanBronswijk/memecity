#ifndef HEALTHCHANGEDARGS_H
#define HEALTHCHANGEDARGS_H
#include <ECS.h>

struct HealthChangedEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	const int new_health;

	HealthChangedEventArgs(const int new_health) : new_health(new_health) {}
};
#endif // HEALTHCHANGEDARGS_H

#ifndef HEALTHCHANGEDARGS_H
#define HEALTHCHANGEDARGS_H
#include <ECS.h>

struct HealthEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	int new_health;

	 HealthEventArgs(const int new_health) : new_health(new_health) {}
};
#endif // HEALTHCHANGEDARGS_H


#ifndef EXPEVENTARGS_H
#define EXPEVENTARGS_H
#include <ECS.h>

struct ExpEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	const int new_Exp;

	ExpEventArgs(const int new_health) : new_Exp(new_health) {}
};
#endif // EXPEVENTARGS_H

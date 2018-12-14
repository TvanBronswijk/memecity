
#ifndef EXPEVENTARGS_H
#define EXPEVENTARGS_H
#include <ECS.h>

struct ExpEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	int new_Exp;

	explicit ExpEventArgs(const int new_exp) : new_Exp(new_exp) {}
};
#endif // EXPEVENTARGS_H

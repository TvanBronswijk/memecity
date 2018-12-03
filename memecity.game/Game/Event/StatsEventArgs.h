

#ifndef STATSEVENTARGS_H
#define STATSEVENTARGS_H
#include <ECS.h>

struct StatsEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	StatsEventArgs(int s, int p, int e, int c, int i, int a, int l)
	: s(s), p(p), e(e), c(c), i(i), a(a), l(l) { }

	const int s, p, e, c, i, a, l;
};
#endif // STATSEVENTARGS_H

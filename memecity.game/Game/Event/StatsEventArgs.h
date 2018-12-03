

#ifndef STATSEVENTARGS_H
#define STATSEVENTARGS_H
#include <ECS.h>

struct StatsEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	StatsEventArgs(int s, int p, int e, int c, int i, int a, int l)
		: S(s),
		  P(p),
		  E(e),
		  C(c),
		  I(i),
		  A(a),
		  L(l)
	{
	}

	const int S;
	const int P;
	const int E;
	const int C;
	const int I;
	const int A;
	const int L;

	//StatsEventArgs(const int new_score) : new_score(new_score) {}
};
#endif // STATSEVENTARGS_H

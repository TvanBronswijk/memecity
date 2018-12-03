
#ifndef BLIKCOINEVENTARG_H
#define BLIKCOINEVENTARG_H
#include <ECS.h>

struct BlikCoinEventArg : public  memecity::engine::ecs::eventing::EventArgs
{
	explicit BlikCoinEventArg(int new_coin)
		: new_coin(new_coin)
	{
	}

	const int new_coin;

};
#endif // BLIKCOINEVENTARG_H

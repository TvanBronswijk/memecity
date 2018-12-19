#ifndef BLIKCOIN_EVENT_ARGS_H
#define BLIKCOIN_EVENT_ARGS_H
#include <ECS.h>

struct BlikCoinEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	explicit BlikCoinEventArgs(int new_coin)
		: new_coin(new_coin)
	{
	}

	int new_coin;

};
#endif // BLIKCOINEVENTARG_H

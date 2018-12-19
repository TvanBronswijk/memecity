#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include <queue>
#include "..\Models\Models.h"

namespace generate::strategy {
	class Strategy {
	protected:
		std::queue<const models::Prefab*> _prefabs;
	public:
		Strategy() = default;
		Strategy(std::queue<const models::Prefab*> prefabs) : _prefabs(std::move(prefabs)) {}
		virtual ~Strategy() = default;
		virtual models::City generate(int w, int h) = 0;
	};
}

#endif

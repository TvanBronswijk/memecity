#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include <vector>
#include "..\Models\Models.h"

namespace generate::strategy {
	class Strategy {
	protected:
		size_t _prefab_index;
		std::vector<models::Prefab> _prefabs;
	public:
		Strategy() noexcept = default;
		Strategy(std::vector<models::Prefab> prefabs) : _prefab_index(0), _prefabs(prefabs) {}
		virtual ~Strategy() = default;
		virtual models::City generate(int w, int h) = 0;
		virtual models::Prefab* get_next_prefab() {
			if (_prefab_index >= _prefabs.size()) {
				return nullptr;
			}
			return &(_prefabs[_prefab_index++]);
		}
	};
}

#endif

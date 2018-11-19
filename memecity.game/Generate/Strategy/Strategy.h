#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include "..\Models\Models.h"

namespace generate::strategy {
	class Strategy {
	public:
		virtual models::City generate(int w, int h) const = 0;
	};
}

#endif

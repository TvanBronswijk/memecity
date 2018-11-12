#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include "..\Models\Models.h"

namespace generate {
	namespace strategy {
		class Strategy {
		public:
			virtual generate::models::City generate(int w, int h) const = 0;
		};
	}
}

#endif

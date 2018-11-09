#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include "City.h"

namespace generate {
	namespace strategy {
		class GeneratorStrategy {
		public:
			virtual generate::models::City generate(int w, int h) const = 0;
		};
	}
}

#endif

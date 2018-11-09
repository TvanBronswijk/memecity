#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include "City.h"

namespace generate {
	namespace strategy {
		class GeneratorStrategy {
		public:
			virtual std::unique_ptr<generate::models::City> generate(int w, int h) = 0;
		};
	}
}

#endif

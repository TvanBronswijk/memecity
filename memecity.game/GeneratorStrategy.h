#ifndef _GENERATOR_STRATEGY_H
#define _GENERATOR_STRATEGY_H
#include <iostream>
#include "City.h"

class GeneratorStrategy {
public:
	virtual std::unique_ptr<City> generate(int w, int h) = 0;
};

#endif
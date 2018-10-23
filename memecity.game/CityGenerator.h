#ifndef _CITY_GENERATOR_H
#define _CITY_GENERATOR_H
#include <iostream>
#include "GeneratorStrategy.h"
#include "BSPGenerator.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "DrawableComponent.h"
#include "MultimediaManager.h"

class CityGenerator {
private:
	std::unique_ptr<BSPGenerator> strategy;
public:
	CityGenerator();
	void generate(int w, int h, std::unique_ptr<EntityManager> &em, std::shared_ptr<MultimediaManager> multimedia_manager);
};

#endif
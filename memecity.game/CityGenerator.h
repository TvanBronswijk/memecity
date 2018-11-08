#ifndef _CITY_GENERATOR_H
#define _CITY_GENERATOR_H
#include <ECS.h>
#include "MultimediaManager.h"
#include "GeneratorStrategy.h"
#include "BSPGenerator.h"

class CityGenerator {
private:
	std::unique_ptr<BSPGenerator> strategy;
public:
	CityGenerator();
	void generate(int w, int h, ecs::EntityManager& em, MultimediaManager &multimedia_manager);
};

#endif
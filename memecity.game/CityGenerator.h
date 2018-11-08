#ifndef _CITY_GENERATOR_H
#define _CITY_GENERATOR_H
#include "../memecity.engine.ecs/ECS.h"
#include "MultimediaManager.h"
#include "GeneratorStrategy.h"
#include "BSPGenerator.h"
#include "DrawableComponent.h"

class CityGenerator {
private:
	std::unique_ptr<BSPGenerator> strategy;
public:
	CityGenerator();
	void generate(int w, int h, ecs::EntityManager& em, MultimediaManager &multimedia_manager);
};

#endif
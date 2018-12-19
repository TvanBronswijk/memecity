#include "CityGenerator.h"
#include "Strategy\BSP\BSP.h"

generate::CityGenerator::CityGenerator(int width, int height) : _w(width), _h(height)
{
	std::queue<const models::Prefab*> queue;
	queue.push(&models::station);
	set_strategy<generate::strategy::bsp::BSP>(std::move(queue));
}

generate::models::City generate::CityGenerator::generate() const
{
	return _strategy->generate(_w, _h);
}

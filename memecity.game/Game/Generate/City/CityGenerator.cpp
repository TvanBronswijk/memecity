#include "CityGenerator.h"
#include "Strategy\BSP\BSP.h"

generate::CityGenerator::CityGenerator(int width, int height) : _w(width), _h(height)
{
	set_strategy<generate::strategy::bsp::BSP>(std::vector<const models::Prefab*>{ &generate::models::station });
}

generate::models::City generate::CityGenerator::generate() const
{
	return _strategy->generate(_w, _h);
}

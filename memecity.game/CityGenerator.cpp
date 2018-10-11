#include "CityGenerator.h"

std::unique_ptr<City> CityGenerator::generate(int w, int h)
{
	auto c = std::make_unique<City>(w, h);

	Node root;
	root.x = 0;
	root.y = 0;
	root.w = c->w;
	root.h = c->h;

	

	return c;
}

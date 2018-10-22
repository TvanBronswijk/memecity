#include "CityGenerator.h"

CityGenerator::CityGenerator()
{
	this->strategy = std::make_unique<BSPGenerator>();
}

void CityGenerator::generate(int w, int h, std::unique_ptr<EntityManager> &em)
{
	auto c = this->strategy->generate(w, h);

	for (int x = c->x; x < c->x2; x++) {
		for (int y = c->y; y < c->y2; y++) {
			std::cout << c->coord(y, x);
		}
		std::cout << std::endl;
	}
}

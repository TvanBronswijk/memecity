#include "CityGenerator.h"

using namespace ecs;

CityGenerator::CityGenerator()
{
	this->strategy = std::make_unique<BSPGenerator>();
}

void CityGenerator::generate(int w, int h, std::unique_ptr<EntityManager> &em, std::shared_ptr<MultimediaManager> multimedia_manager)
{
	auto c = this->strategy->generate(w, h);

	for (int x = c->x; x < c->x2; x++) {
		for (int y = c->y; y < c->y2; y++) {
			auto character = c->coord(x, y);

			std::cout << character;
			auto entity = em->create_entity();
			auto drawable_component = new DrawableComponent(entity);
			auto filename = "purple.bmp";

			switch (character)
			{
			case  '-':
				filename = "gray.bmp";
				break;
			case  'W':
				filename = "brown.bmp";
				break;
			case  'w':
				filename = "blue.bmp";
				break;
			case 'g':
				filename = "green.bmp";
				break;
			}
			auto texture = multimedia_manager->get_texture(filename);
			texture->set_position({ x * 64.0f, y * 64.0f });
			drawable_component->texture = texture;

			em->register_component(drawable_component);
		}
		std::cout << std::endl;
	}
}

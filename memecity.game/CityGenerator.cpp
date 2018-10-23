#include "CityGenerator.h"

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
			auto component = new DrawableComponent(entity);

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

			if (character == 'W' || character == 'w')
			{
				em->register_component(new ColliderComponent(entity, x * 16.0f, y * 16.0f, 16, 16));
			}

			auto texture = multimedia_manager->get_texture(filename, 0, 0, 16, 16);
			texture->set_position({ x * 16.0f, y * 16.0f });
			component->texture = texture;

			em->register_component(component);
		}
		std::cout << std::endl;
	}
}

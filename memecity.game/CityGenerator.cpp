#include "CityGenerator.h"
#include "DrawableComponent.h"

using namespace ecs;

void generate::CityGenerator::generate(int w, int h, EntityManager& em, MultimediaManager &multimedia_manager) const
{
	const auto& c = this->strategy->generate(w, h);

	for (int x = c.x; x < c.x2; x++) {
		for (int y = c.y; y < c.y2; y++) {
			auto& character = c.coord(x, y);

			std::cout << character;
			auto& entity = em.create_entity();
			auto& drawable_component = em.create_component<DrawableComponent>(entity);
			
			std::string filename;
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
			default:
				std::cout << "ERROR!" << std::endl;
			}
			auto texture = multimedia_manager.get_texture(filename);
			texture->set_position({ x * 64.0f, y * 64.0f });
			drawable_component.texture = texture;
		}
		std::cout << std::endl;
	}
}

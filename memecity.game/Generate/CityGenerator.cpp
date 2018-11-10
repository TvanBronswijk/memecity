#include "CityGenerator.h"
#include "..\DrawableComponent.h"

using namespace ecs;

void generate::CityGenerator::generate(int w, int h, EntityManager& em, MultimediaManager &multimedia_manager) const
{
	const auto& c = this->strategy->generate(w, h);
	
	for (int y = c.y; y < c.y2; y++) {
		for (int x = c.x; x < c.x2; x++) {
			auto& character = c.coord(x, y);
			std::cout << character;
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
			builder::EntityBuilder(em)
				.add_component<DrawableComponent>(texture)
				.build();
		}
		std::cout << std::endl;
	}
}

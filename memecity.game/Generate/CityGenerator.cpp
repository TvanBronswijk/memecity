#include "CityGenerator.h"
#include "Strategy\BSP\BSP.h"
#include "..\Components.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

generate::CityGenerator::CityGenerator()
{
	set_strategy<generate::strategy::bsp::BSP>();
}

void generate::CityGenerator::generate(int w, int h, EntityManager& em, MultimediaManager &multimedia_manager) const
{
	const auto& c = this->_strategy->generate(w, h);

	for (int y = c.begin.y; y < c.end.y; y++) {
		for (int x = c.begin.x; x < c.end.x; x++) {
			auto& character = c(x, y);
#ifdef DEBUG
			std::cout << character;
#endif
			std::string filename;
			switch (character)
			{
			case '-':
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

			auto& builder = builder::EntityBuilder(em)
				.create_entity()
				.with_component<DrawableComponent>(std::move(texture));
			if (character == 'W' || character == 'w')
			{
				builder
					.with_component<ColliderComponent>(64.0f, 64.0f)
					.with_component<PositionComponent>(x * 64.0f, y * 64.0f);
			}
		}
#ifdef DEBUG
		std::cout << '\n';
#endif
	}
}

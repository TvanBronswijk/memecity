#include "CityGenerator.h"
#include "Strategy\BSP\BSP.h"
#include "..\Components.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

generate::CityGenerator::CityGenerator()
{
	set_strategy<generate::strategy::bsp::BSP>();
}

void generate::CityGenerator::generate(int w, int h, EntityManager& em, MultimediaManager &multimedia_manager, QuadTree &quad_tree) const
{
	auto zero = 0.0f;
	auto screen_width = w * 64.0f;
	auto screen_height = h * 64.0f;
	auto boundary = BoundaryRectangle(zero, zero, screen_width, screen_height);
	quad_tree = QuadTree(4, boundary);

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

			auto& builder = builder::EntityBuilder(em)
				.create_entity()
				.with_component<DrawableComponent>(std::move(texture));
			if (character == 'W' || character == 'w')
			{
				builder
					.with_component<ColliderComponent>(64.0f, 64.0f)
					.with_component<PositionComponent>(x * 64.0f, y * 64.0f);

				auto collider_x = x * 64.0f;
				auto collider_y = y * 64.0f;
				auto test = 64.0f;
				auto boundary = BoundaryRectangle(collider_x, collider_y, test, test);
				quad_tree.insert(boundary);
			}
		}
		std::cout << std::endl;
	}
}

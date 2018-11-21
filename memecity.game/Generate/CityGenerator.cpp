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
	quad_tree = QuadTree(16, Rectangle(0, 0, w * 64.0f, h * 64.0f));
	const auto& c = this->_strategy->generate(w, h);

	for (int y = c.begin.y; y < c.end.y; y++) {
		for (int x = c.begin.x; x < c.end.x; x++) {
			auto& character = c(x, y);
			std::cout << character;
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
				auto& entity = builder
					.with_component<DimensionComponent>(64.0f, 64.0f)
					.with_component<PositionComponent>(x * 64.0f, y * 64.0f).get();

				auto dimension_component = entity.get<DimensionComponent>();
				auto position_component = entity.get<PositionComponent>();

				builder
				.with_component<ColliderComponent>(BoundaryRectangle(position_component->x, position_component->y, dimension_component->w, dimension_component->h));

				auto collider_component = entity.get<ColliderComponent>();

				quad_tree.insert(collider_component->boundary_rectangle);
			}
		}
		std::cout << std::endl;
	}
}

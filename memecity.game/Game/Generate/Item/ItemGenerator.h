#ifndef _ITEMGENERATOR_H
#define  _ITEMGENERATOR_H
#include <ECS.h>
#include <Engine\MultimediaManager.h>
#include "..\..\..\Assets.h"
namespace generate {
	class ItemGenerator {
	private:
		memecity::engine::MultimediaManager* multimedia_manager;
		memecity::engine::ecs::EntityManager* entity_manager;
	public:
		void make_all_items();

		const memecity::engine::ecs::Entity* make_item(std::string name, std::string description,
			int strength, int perception, int endurance, int charisma, int intelligence, int agility, int luck,
			int x, int y, int width, int height, assets::Asset asset);
		ItemGenerator(
			memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager) :
			entity_manager(&entity_manager), multimedia_manager(&multimedia_manager) {}
	};
}

#endif


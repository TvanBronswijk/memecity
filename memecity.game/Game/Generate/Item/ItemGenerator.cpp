#include "ItemGenerator.h"
#include "..\..\Components.h"
#include "..\..\..\Assets.h"

namespace generate {
	//place to make all items that needed to be generated when the world is loading.
	void ItemGenerator::MakeAllItems() {
		//MakeItem("Tin can", "a normal tin can", 0, 0, 0, 0, 0, 0, 0, 50, 0, 48, 48, assets::sprites::TIN_CAN);
	}


	const memecity::engine::ecs::Entity* ItemGenerator::MakeItem(std::string name, std::string description,
		int strength, int perception, int endurance, int charisma, int intelligence, int agility, int luck,
		int x, int y, int width, int height, assets::Asset asset) {

		auto texture = multimedia_manager.get_texture(asset, 0, 0, width, height);
		texture->set_position({ 0,0 });

		const char* entity_name = name.c_str();
		auto& entity = entity_manager.create_entity(entity_name)
			.with_component<BaseComponent>(std::move(texture), x, y, width, height)
			.with_component<ItemComponent>(name, description)
			.with_component<StatsComponent>(strength, perception, endurance, charisma, intelligence, agility, luck)
			.get();

		return &entity;
	}
}

#include "ItemGenerator.h"
#include "..\..\Components.h"
#include "..\..\..\Assets.h"

namespace generate {
	void ItemGenerator::MakeAllItems() {
		auto texture = multimedia_manager.get_texture(assets::sprites::TIN_CAN, 0, 0, 48, 28);
		texture->set_position({ 0,0 });

		auto builder = entity_manager.create_entity("Blik")
			.with_component<BaseComponent>(std::move(texture), 50.0f, 0.0f, 48.0f, 48.0f)
			.with_component<ItemComponent>("Blik", "a normal tin can")
			.with_component<StatsComponent>(0, 0, 0, 0, 0, 0, 0);
	}
}

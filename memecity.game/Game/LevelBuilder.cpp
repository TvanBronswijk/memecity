#include "LevelBuilder.h"
#include "Generate.h"
#include "Components.h"
#include "Systems.h"
#include "..\Assets.h"
#include "Generate/City/Strategy/File/FileStrategy.h"

using namespace memecity::engine::ecs;
using namespace memecity::engine::ui;

Point LevelBuilder::build(memecity::engine::ecs::EntityManager& em, loading::LoadingBar::Listener& listener, int& _map_number)
{
	listener.set_max_value(100.0f);
	listener.set_current_value(0.0f);
	auto& multimedia_manager = _context->get_multimedia_manager();
	auto generator = generate::CityGenerator(_context->get_storage_manager(), _map_width, _map_height);
	if (_load_from_file)
	{
		auto active_map_number = _context->get_storage_manager().load_string(assets::saves::SAVE_LOCATION + std::string("//") + _save_location + "//" + assets::saves::SAVE_MAP_ACTIVE);
		active_map_number.erase(std::remove(active_map_number.begin(), active_map_number.end(), '\n'), active_map_number.end());
		std::string save = assets::saves::SAVE_LOCATION;
		save += "\\" + _save_location + "\\" +assets::saves::SAVE_MAP + active_map_number+".txt";
		generator.set_strategy<generate::strategy::FileStrategy>(_context->get_storage_manager().load_string(save));
		_map_number = stoi(active_map_number);
	}

	generate::models::City city = generator.generate();
	for (int y = 0; y < city.height; y++) {
		for (int x = 0; x < city.width; x++) {
			auto& tile = city.tiles(x, y);
			auto tile_info = generate::models::char_to_tile(tile);
			if (tile_info.name != "Not Found") {
				auto& builder = em.create_entity("tile")
					.with_component<BaseComponent>(multimedia_manager.get_texture(tile_info.get_asset()), x * 64.0f, y * 64.0f, 64.0f, 64.0f)
					.with_component<TileComponent>(tile_info.name, tile_info.blocked, tile_info.block_sight, tile);
				if (tile_info.blocked) {
					auto base_component = builder.get().get<BaseComponent>();
					builder.with_component<ColliderComponent>(BoundaryRectangle{ base_component->location.x, base_component->location.y, base_component->w, base_component->h });
				}
				listener.increase_current_value((100.0f / (_map_width*_map_height)) / 2);
			}

			auto& object = city.objects(x, y);
			switch (object)
			{
			case 'p':
				generate::NPCGenerator(_context->get_multimedia_manager(), em).generate_police_npc(x*64.0f, y*64.0f);
				break;
			case 'n':
				generate::NPCGenerator(_context->get_multimedia_manager(), em).generate_civilian_npc(x*64.0f, y*64.0f);
				break;
			case 'c':
				auto texture = multimedia_manager.get_texture(assets::sprites::TIN_CAN, 0, 0, 48, 28);
				texture->set_position({ 0,0 });
				auto builder = em.create_entity("Tin can")
					.with_component<BaseComponent>(std::move(texture), x * 64.0f, y * 64.0f, 48.0f, 48.0f)
					.with_component<ItemComponent>("Tin can", "a normal tin can")
					.with_component<StatsComponent>(0, 0, 0, 0, 0, 0, 0);
				auto base_component = builder.get().get<BaseComponent>();
				builder.with_component<ColliderComponent>(BoundaryRectangle(base_component->location.x, base_component->location.y, base_component->w, base_component->h));
				break;
			}
			listener.increase_current_value((100.0f / (_map_width*_map_height)) / 2);
		}
	}
	listener.set_current_value(100.0f);
	return { static_cast<float>(city.start.x) * 64.0f, static_cast<float>(city.start.y) * 64.0f };
}



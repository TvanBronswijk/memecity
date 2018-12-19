#include "GameSaver.h"
#include "PlayerManager.h"
#include "../Assets.h"
#include "MapSaver.h"
#include "../GameManager.h"

bool GameSaver::save(memecity::engine::ecs::EntityManager& em, GameManager::GameContext& context, std::string save_slot, int map_number)
{
	const auto player_manager = PlayerManager(em);
	const auto player_data = player_manager.save_player();
	std::string save_location = assets::saves::SAVE_LOCATION;
	const auto success = context.get_storage_manager().save(save_location + "\\" + save_slot + "\\" + assets::saves::SAVE_PLAYER, player_data);
	auto map = MapSaver{}.get_map(em);
	auto map_success = context.get_storage_manager().save(save_location + "\\" + save_slot + "\\" + assets::saves::SAVE_MAP+std::to_string(map_number)+".txt", map);
	context.get_storage_manager().save(save_location + "\\" + save_slot + "\\" + assets::saves::SAVE_MAP_ACTIVE, std::to_string(map_number));
	return success && map_success;
}

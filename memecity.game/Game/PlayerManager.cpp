﻿#include "PlayerManager.h"
#include "Components/PlayerComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/StatsComponent.h"

memecity::engine::serialization::SerializeInfo PlayerManager::save_player() const
{
	memecity::engine::serialization::SerializeInfo map;
	std::vector<memecity::engine::serialization::SerializeInfo> result_maps;

	auto& player_component = _entity_manager->get_components_of_type<PlayerComponent>().front().get();
	const auto& player_entity = player_component.entity();

	result_maps.push_back(player_entity.get<ScoreComponent>()->to_map());

	std::for_each(result_maps.begin(), result_maps.end(), [&map](const std::map<std::string, std::string> result)
	{
		map.insert(result.begin(), result.end());
	});

	return map;
}

bool PlayerManager::load_player(memecity::engine::serialization::SerializeInfo& data) const
{
	auto& player_component = _entity_manager->get_components_of_type<PlayerComponent>().front().get();
	const auto& player_entity = player_component.entity();
	player_entity.get<ScoreComponent>()->from_map(data);
	return true;
}

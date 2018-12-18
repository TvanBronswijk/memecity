#include "PlayerManager.h"
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
	result_maps.push_back(player_entity.get<StatsComponent>()->to_map());

	std::for_each(result_maps.begin(), result_maps.end(), [&](const memecity::engine::serialization::SerializeInfo data)
	{
		map.insert(data.begin(), data.end());
	});

	return map;
}

bool PlayerManager::load_player(memecity::engine::serialization::SerializeInfo& data) const
{
	auto& player_component = _entity_manager->get_components_of_type<PlayerComponent>().front().get();
	const auto& player_entity = player_component.entity();

	std::for_each(data.begin(), data.end(), [&](const std::pair<std::string, std::string> pair)
	{
		auto key = pair.first;
		const auto component = std::string(key.substr(0, key.find(':')));
		key = key.substr(key.find(':') + 1, key.find('='));
		const auto value = std::string(pair.second);

		const std::pair<std::string, std::string> component_pair{ key, value };

		std::cout << "Component: " << component << ", " << "Key: " << key << ", Value: " << value << "\n";

		if (component == "ScoreComponent")
		{
			player_entity.get<ScoreComponent>()->from_pair(component_pair);
			return;
		}

		if (component == "StatsComponent")
		{
			player_entity.get<StatsComponent>()->from_pair(component_pair);
		}
	});

	return true;
}

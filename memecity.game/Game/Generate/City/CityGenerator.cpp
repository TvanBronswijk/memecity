#include "CityGenerator.h"
#include "Strategy\BSP\BSP.h"

generate::CityGenerator::CityGenerator(memecity::engine::StorageManager& storage, int width, int height) : _w(width), _h(height)
{
	std::queue<const models::Prefab*> queue;
	queue.push(&models::station);

	auto prefab_dir = storage.load_files_from_directory("Assets/Scripts/Prefabs");
	for (auto& pair : prefab_dir) {
		auto str = pair.second;
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		int w, h;
		w = 16;
		h = 16;
		_prefabs.push_back(models::Prefab{ w, h, str.c_str(), " " });
	}

	for (auto& prefab : _prefabs) {
		queue.push(&prefab);
	}

	set_strategy<generate::strategy::bsp::BSP>(std::move(queue));
}

generate::models::City generate::CityGenerator::generate() const
{
	return _strategy->generate(_w, _h);
}

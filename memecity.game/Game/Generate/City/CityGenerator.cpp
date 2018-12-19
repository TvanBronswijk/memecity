#include "CityGenerator.h"
#include "Strategy\BSP\BSP.h"

generate::CityGenerator::CityGenerator(memecity::engine::StorageManager& storage, int width, int height) : _w(width), _h(height)
{
	std::queue<const models::Prefab*> queue;
	queue.push(&models::station);

	auto prefab_dir = storage.load_files_from_directory("Assets/Scripts/Prefabs");
	for (auto& pair : prefab_dir) {
		if (pair.first.path().extension() == ".m2d") {
			auto other_pair = std::find_if(prefab_dir.begin(), prefab_dir.end(), [&](auto& other_pair) 
			{ return other_pair.first.path().stem() == pair.first.path().stem() && other_pair.first.path().extension() == ".m2do"; });
			
			auto content = pair.second;
			content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
			auto objects = other_pair->second;
			objects.erase(std::remove(objects.begin(), objects.end(), '\n'), objects.end());
			_prefabs.push_back(models::Prefab{ 16, 16, content.c_str(), objects.c_str() });
		}
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

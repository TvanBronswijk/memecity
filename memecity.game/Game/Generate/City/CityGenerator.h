#ifndef _CITY_GENERATOR_H
#define _CITY_GENERATOR_H
#include <vector>
#include <Engine\MultimediaManager.h>
#include <Engine/StorageManager.h>
#include <ECS.h>
#include "Models\Models.h"
#include "strategy\Strategy.h"

namespace generate {
	class CityGenerator {
	private:
		int _w, _h;
		std::vector<models::Prefab> _prefabs;
		std::unique_ptr<strategy::Strategy> _strategy;
	public:
		CityGenerator(memecity::engine::StorageManager& storage, int width, int _height);

		template<class T, class... Args>
		void set_strategy(Args&&... args)
		{
			static_assert(std::is_convertible<T*, strategy::Strategy*>::value, "Only Generator Strategies can be set.");
			static_assert(std::is_constructible<T, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			_strategy = std::make_unique<T>(std::forward<Args>(args)...);
		}
		models::City generate() const;
		~CityGenerator() = default;
	};
}

#endif

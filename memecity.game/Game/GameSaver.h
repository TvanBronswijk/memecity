#ifndef GAMESAVER_H
#define GAMESAVER_H
#include "../GameManager.h"

namespace memecity {
	namespace engine {
		namespace ecs {
			class EntityManager;
		}
	}
}

class GameSaver
{

public:

	bool save(memecity::engine::ecs::EntityManager& em, GameManager::GameContext& context, std::string save_slot, int map_number);
	

	
};
#endif // GAMESAVER_H

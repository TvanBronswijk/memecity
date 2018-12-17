#ifndef _PLAYER_MANAGER_H
#define _PLAYER_MANAGER_H

#include "ECS/EntityManager.h"
#include "Engine/Serialize.h"

class PlayerManager
{
private:
	memecity::engine::ecs::EntityManager* _entity_manager;

public:
	PlayerManager(memecity::engine::ecs::EntityManager &em) 
		: _entity_manager(&em) {}
	
	memecity::engine::serialization::SerializeInfo get_player_map() const;
};

#endif
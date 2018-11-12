#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include "../memecity.engine.ecs/EntityManager.h"
#include "../memecity.engine.ecs/System.h"
#include "velocityComponent.h"
#include "PositionComponent.h"
#include <list>

class AISystem : public ecs::System {

private:
	int random_x(VelocityComponent* velocity) const;
	int random_y(VelocityComponent* velocity) const;
	void move_random(const ecs::Entity& entity, ecs::EntityManager& em) const;
	bool check_health(ecs::EntityManager& em, ecs::Component& element) const;
	void best_first_search(ecs::EntityManager& em, PositionComponent& xy) const;
	std::list <std::pair< int, int >> calculate_next_positions(std::pair< int, int > start, std::pair< int, int > end, std::list <std::pair< int, int >> queue) const;
	bool check_player_position_X(std::pair<int, int> location, std::pair<int, int> end) const;
	bool check_player_position_Y(std::pair<int, int> location, std::pair<int, int> end) const;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	static const int range = 5;

	AISystem();
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return AISystem::SYSTEM_TYPE; }
};

#endif

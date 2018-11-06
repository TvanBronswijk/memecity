#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "PositionComponent.h"
#include "velocityComponent.h"
#include "AIComponent.h"
#include "HealthComponent.h"
#include "StatsComponent.h"
#include "LevelComponent.h"
#include "playerComponent.h"
#include "drawableComponent.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include <cstdlib>
#include <list>

class AISystem : public System {

	static std::string SYSTEM_TYPE;
	static const int range = 5;

private:
	int random_x(VelocityComponent* velocity);
	int random_y(VelocityComponent* velocity);
	bool check_health(EntityManager & em, Component*& element);
	void best_first_search(EntityManager & em, PositionComponent* xy);
	std::list <std::pair< int, int >> calculate_next_positions(std::pair< int, int > start, std::pair< int, int > end, std::list <std::pair< int, int >> queue);
	bool check_player_position_X(std::pair<int, int> location, std::pair<int, int> end);
	bool check_player_position_Y(std::pair<int, int> location, std::pair<int, int> end);
public:
	AISystem();

	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, EventArgs& e) override;
	void move_random(int element, EntityManager &em);
};

#endif

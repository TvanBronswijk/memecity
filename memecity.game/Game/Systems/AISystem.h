#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include <queue>
#include <ECS.h>
#include <Engine\Util.h>
#include "..\Components.h"

class AISystem : public memecity::engine::ecs::System {

private:
	bool check_health(const memecity::engine::ecs::Entity& entity) const;
	//Roaming
	int random_x() const;
	int random_y() const;
	void move_random(const memecity::engine::ecs::Entity& entity) const;
	//Fighting
	void best_first_search(memecity::engine::ecs::EntityManager& em, const BaseComponent& xy) const;
	std::queue<Point> calculate_next_positions(Point start, Point end, std::queue<Point> queue) const;
	bool check_player_position_X(Point location, Point end) const;
	bool check_player_position_Y(Point location, Point end) const;
	//Fleeing
	void fleeing(memecity::engine::ecs::EntityManager& em, const BaseComponent& xy) const;
public:
	static const int range = 5;
	void run(memecity::engine::ecs::EntityManager& em) const override;
};

#endif

#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include <list>

struct Point {
	float x, y;
	Point(float x, float y) : x(x), y(y) {};
};

class AISystem : public memecity::engine::ecs::System {

private:
	float movement = 0.2f;

	bool check_health(memecity::engine::ecs::EntityManager& em, const memecity::engine::ecs::Entity& entity) const;
	//Roaming
	int random_x() const;
	int random_y() const;
	void move_random(const memecity::engine::ecs::Entity& entity) const;
	//Fighting
	void best_first_search(memecity::engine::ecs::EntityManager& em, const PositionComponent& xy) const;
	std::list <Point> calculate_next_positions(Point start, Point end, std::list <Point> queue) const;
	bool check_player_position_X(Point location, Point end) const;
	bool check_player_position_Y(Point location, Point end) const;
	//Fleeing
	void fleeing(memecity::engine::ecs::EntityManager& em, const PositionComponent& xy) const;
public:
	static const int range = 5;
	void run(memecity::engine::ecs::EntityManager& em) const override;
};

#endif

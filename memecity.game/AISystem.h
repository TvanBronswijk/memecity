#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include <ECS.h>
#include "velocityComponent.h"
#include "PositionComponent.h"
#include <list>

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {};
};

class AISystem : public ecs::System {

private:
	int random_x() const;
	int random_y() const;
	void move_random(const ecs::Entity& entity, ecs::EntityManager& em) const;
	bool check_health(ecs::EntityManager& em, const ecs::Entity& entity) const;
	void best_first_search(ecs::EntityManager& em, PositionComponent& xy) const;
	std::list <Point> calculate_next_positions(Point start, Point end, std::list <Point> queue) const;
	bool check_player_position_X(Point location, Point end) const;
	bool check_player_position_Y(Point location, Point end) const;
public:
	static const int range = 5;
	void run(ecs::EntityManager& em) const override;
};

#endif

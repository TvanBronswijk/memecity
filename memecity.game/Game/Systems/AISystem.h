#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include <queue>
#include <ECS.h>
#include <Engine\Util.h>
#include "..\Components.h"
#include "..\Event\AttackEventArgs.h"

class AISystem : public memecity::engine::ecs::System {

private:
	bool check_health(const memecity::engine::ecs::Entity& entity) const;
	bool check_collision(BaseComponent& l, BaseComponent& r, int range) const;
	//Roaming
	int random_x() const;
	int random_y() const;
	void move_random(const memecity::engine::ecs::Entity& entity) const;
	//Fighting
	void point_jump_search(memecity::engine::ecs::EntityManager& em, BaseComponent& xy) const;
	Point calculate_next_route(Point start, Point end, int speed) const;
	bool check_player_position(Point location, Point end) const;
	//Fleeing
	void fleeing(memecity::engine::ecs::EntityManager& em, const BaseComponent& xy) const;
public:
	memecity::engine::ecs::eventing::Event<AttackEventArgs> attack_event;
	static const int range = 10;
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
};

#endif

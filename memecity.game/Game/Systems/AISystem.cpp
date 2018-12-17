#include "AISystem.h"
#include <vector>

using namespace memecity::engine::ecs;


bool AISystem::check_health(const Entity& entity) const{
	auto AI = entity.get<AIComponent>();
	auto health = entity.get<HealthComponent>();
	if(health->health <= 0) {
		return false;
	}
	else if (health->health < (health->maxhealth * .10)) {
		AI->state = AIComponent::State::Fleeing;
	}
	return true;
}

int AISystem::random_x() const {return (rand() % (2 - -1)) + -1;}
int AISystem::random_y() const {return (rand() % (2 - -1)) + -1;}

std::queue<Point> AISystem::calculate_next_positions(Point start , Point end, std::queue<Point> queue) const{
	if (start.x < end.x - range) { start.x += 10; }
	else if (start.x >  end.x + range) { start.x -= 10;}
	if (start.y < end.y - range) { start.y += 10; }
	else if(start.y > end.y + range) { start.y -= 10;}

	queue.push(Point(start.x - (start.x * 2), start.y - (start.y * 2)));
	queue.push(Point(start.x - (start.x * 2), start.y));
	queue.push(Point(start.x, start.y - (start.x * 2)));
	queue.push(Point(start.x, start.y));

	return queue;
}

bool AISystem::check_player_position_Y(Point location, Point end) const{
	if ((location.y >= end.y - range) && (location.y <= end.y + range)) {
		return true;
	}
	return false;
}

bool AISystem::check_player_position_X(Point location , Point end) const{
	if ((location.x >= end.x - range) && (location.x <= end.x + range)) {
		return true;
	}
	return false;
}


void AISystem::best_first_search(EntityManager& em, const BaseComponent& npc_xy) const{
	auto velocity = npc_xy.entity().get<VelocityComponent>();
	auto& player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_base = player.get<BaseComponent>();

	Point end(player_base->location.x, player_base->location.y); // end location
	Point start(npc_xy.location.x, npc_xy.location.y); // start location

	std::vector<Point> path; // path to end location
	std::queue<Point> queue; // need to visited these positions

	queue = calculate_next_positions(start, end, queue);

	while (!queue.empty()) {
		Point location = queue.front();
		queue.pop();
		path.push_back(location);
		if (check_player_position_X(location, end) && check_player_position_Y(location, end)) {
			queue = {};
		}
		else { 
			queue = calculate_next_positions(location, end, queue); 
		}
	}
	auto direction = path.front();
	if (npc_xy.location.x < direction.x) {
		if (!check_player_position_X(direction, end)) velocity->x += 3;
	}
	else if(npc_xy.location.x > direction.x){
		if(!check_player_position_X(direction, end)) velocity->x -= 3; 
	}
	if (npc_xy.location.y > direction.y) {
		if (!check_player_position_Y(direction, end)) velocity->y -= 3; 
	}
	else if(npc_xy.location.y < direction.y) {
		if (!check_player_position_Y(direction, end)) velocity->y += 3; 
	}
}

void AISystem::move_random(const Entity& entity) const{

	auto velocity = entity.get<VelocityComponent>();
	velocity->x += random_x();
	velocity->y += random_y();
}

void AISystem::fleeing(EntityManager& em, const BaseComponent& base) const { 
	auto& player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_base = player.get<BaseComponent>();
	auto velocity = base.entity().get<VelocityComponent>();

	velocity->x += base.location.x < player_base->location.x ? 4 : -4;
	velocity->y += base.location.y < player_base->location.y ? 4 : -4;
}

void AISystem::run(EntityManager& em, float dt) const {

	auto player = em.get_entities_with_component<PlayerComponent>().front();
	auto npcs = em.get_entities_with_component<AIComponent>();
	for (const Entity& npc : npcs) {
		auto& state = npc.get<AIComponent>()->state;
		auto base = npc.get<BaseComponent>();
		switch (state)
		{
		case AIComponent::State::Fighting:
			best_first_search(em, *base);
			break;
		case AIComponent::State::Fleeing:
			fleeing(em, *base);
			break;
		case AIComponent::State::Roaming:
			move_random(npc);
			break;
		case AIComponent::State::Idle:
			break;
		default:
			break;
		}
	}
}

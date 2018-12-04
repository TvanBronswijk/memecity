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
#ifdef DEBUG
	std::cout << "player: X: " << end.x << " Y: " << end.y << " Drawable X: " << player_drawable->get_texture().get_position().x << " Y: " << player_drawable->get_texture().get_position().y << std::endl;
	std::cout << "npc: X: " << start.x << " Y: " << start.y << " Drawable X: " << drawable->get_texture().get_position().x << " Y: " << drawable->get_texture().get_position().y << std::endl;
#endif	
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

void AISystem::fleeing(EntityManager& em, const BaseComponent& npc_xy) const { 
	/*auto velocity = npc_xy.entity().get<VelocityComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();
	auto player_position = player_component.entity().get<BaseComponent>();

	if (npc_xy.x < player_position->x) { velocity->x -= 4; }
	else if (npc_xy.x > player_position->x) { velocity->x += 4; }
	if (npc_xy.y < player_position->y) { velocity->y -= 4; }
	else if (npc_xy.y > player_position->y) { velocity->y += 4; }*/
}

void AISystem::run(EntityManager& em) const {
	auto vector = em.get_components_of_type<AIComponent>();
	auto player = em.get_entities_with_component<PlayerComponent>()[0];

	for (auto& element : vector) {
		if (check_health(element.get().entity())) {
			auto AI = element.get().entity().get<AIComponent>();
			auto xy = element.get().entity().get<BaseComponent>();
			switch (AI->state)
			{
			case AIComponent::State::Fighting:
				best_first_search(em, *xy);
				break;
			case AIComponent::State::Fleeing:
				fleeing(em, *xy);
				break;
			case AIComponent::State::Roaming:
				move_random(element.get().entity());
				break;
			case AIComponent::State::Idle:
				break;
			default:
				break;
			}
		}
	}
}

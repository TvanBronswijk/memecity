#include "AISystem.h"

using namespace memecity::engine::ecs;


bool AISystem::check_health(EntityManager& em, const Entity& entity) const{
	auto AI = entity.get<AIComponent>();
	auto health = entity.get<HealthComponent>();
	if(health->health <= 0) {
		return false;
	}
	else if (health->health < (health->maxhealth/10)) {
		AI->state = AIComponent::State::Fleeing;
	}
	return true;
}

int AISystem::random_x() const {return (rand() % (2 - -1)) + -1;}
int AISystem::random_y() const {return (rand() % (2 - -1)) + -1;}

std::list <Point> AISystem::calculate_next_positions(Point start , Point end, std::list <Point> queue) const{
	if (start.x < end.x - range) { start.x += 10; }
	else if (start.x >  end.x + range) { start.x -= 10;}
	if (start.y < end.y - range) { start.y += 10; }
	else if(start.y > end.y + range) { start.y -= 10;}

	queue.push_front(Point(start.x - (start.x * 2), start.y - (start.y * 2)));
	queue.push_front(Point(start.x - (start.x * 2), start.y));
	queue.push_front(Point(start.x, start.y - (start.x * 2)));
	queue.push_front(Point(start.x, start.y));

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


void AISystem::best_first_search(EntityManager& em, const PositionComponent& npc_xy) const{
	auto velocity = npc_xy.entity.get<VelocityComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();

	auto player_position = player_component.entity.get<PositionComponent>();
	auto player_drawable = player_component.entity.get<DrawableComponent>();//testing
	auto drawable = npc_xy.entity.get<DrawableComponent>();//testing

	Point end(player_position->x, player_position->y); // end location
	Point start(npc_xy.x, npc_xy.y); // start location

	std::list <Point> path; // path to end location
	std::list <Point> queue; // need to visited these positions

	queue = calculate_next_positions(start, end, queue);

	while (!queue.empty()) {
		Point location = queue.front();
		queue.pop_front();

		if (path.size() == 0) {
			path.push_back(location);
		}
		else {
			path.push_back(location);
		}
	
		if (check_player_position_X(location, end) && check_player_position_Y(location, end)) {
			queue.clear();
		}
		else { 
			queue = calculate_next_positions(location, end, queue); 
		}
	}
	std::cout << "player: X: " << end.x << " Y: " << end.y << " Drawable X: " << player_drawable->get_texture().get_position().x << " Y: " << player_drawable->get_texture().get_position().y << std::endl;
	std::cout << "npc: X: " << start.x << " Y: " << start.y << " Drawable X: " << drawable->get_texture().get_position().x << " Y: " << drawable->get_texture().get_position().y << std::endl;
	auto direction = path.front();

	if (npc_xy.x < direction.x) { 
		if (!check_player_position_X(direction, end)) velocity->x += 2;
	}
	else if(npc_xy.x > direction.x){
		if(!check_player_position_X(direction, end)) velocity->x -= 2; 
	}
	if (npc_xy.y > direction.y) {
		if (!check_player_position_Y(direction, end)) velocity->y -= 2; 
	}
	else if(npc_xy.y < direction.y) {
		if (!check_player_position_Y(direction, end)) velocity->y += 2; 
	}
}

void AISystem::move_random(const Entity& entity) const{

	auto velocity = entity.get<VelocityComponent>();

	velocity->x += random_x();
	velocity->y += random_y();

}

void AISystem::fleeing(EntityManager& em, const PositionComponent& npc_xy) const { 
	auto velocity = npc_xy.entity.get<VelocityComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();
	auto player_position = player_component.entity.get<PositionComponent>();

	if (npc_xy.x < player_position->x) { velocity->x -= 10; }
	else if (npc_xy.x > player_position->x) { velocity->x += 10; }
	if (npc_xy.y < player_position->y) { velocity->y -= 10; }
	else if (npc_xy.y > player_position->y) { velocity->y += 10; }
}

void AISystem::run(EntityManager& em) const {
	auto vector = em.get_components_of_type<AIComponent>();
	auto player = em.get_entities_with_component<PlayerComponent>()[0];

	for (auto& element : vector) {
		if (check_health(em, element.get().entity)) {
			auto AI = element.get().entity.get<AIComponent>();
			auto xy = element.get().entity.get<PositionComponent>();
			switch (AI->state)
			{
			case AIComponent::State::Fighting:
				best_first_search(em, *xy);
				break;
			case AIComponent::State::Fleeing:
				fleeing(em, *xy);
				break;
			case AIComponent::State::Roaming:
				move_random(element.get().entity);
				break;
			case AIComponent::State::Idle:
				break;
			default:
				break;
			}
		}
	}
}

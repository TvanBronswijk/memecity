#include "AISystem.h"

#include "AIComponent.h"
#include "HealthComponent.h"
#include "StatsComponent.h"
#include "LevelComponent.h"
#include "PlayerComponent.h"
#include "drawableComponent.h"
#include "PositionComponent.h"


using namespace ecs;


bool AISystem::check_health(EntityManager& em, const Entity& entity) const{
	auto AI = entity.get<AIComponent>();
	auto health = entity.get<HealthComponent>();
	if(health->_health <= 0) {
		std::cout << "i am dead!!!" << std::endl;//testing
		return false;
	}
	else if (health->_health <= 10) {
		AI->_state = AI->Fleeing;
	}
	return true;
}

int AISystem::random_x(VelocityComponent* velocity) const {return (rand() % (2 - -1)) + -1;}
int AISystem::random_y(VelocityComponent* velocity) const {return (rand() % (2 - -1)) + -1;}

std::list <std::pair< int, int >> AISystem::calculate_next_positions(std::pair< int, int >start , std::pair< int, int >end, std::list <std::pair< int, int >> queue) const{
	if (start.first < end.first - range) { start.first += 10; }
	else if (start.first >  end.first + range) { start.first -= 10;}
	if (start.second < end.second - range) { start.second += 10; }
	else if(start.second > end.second + range) { start.second -= 10;}

	queue.push_front(std::pair<int, int>(start.first - (start.first * 2), start.second - (start.first * 2)));
	queue.push_front(std::pair<int, int>(start.first - (start.first * 2), start.second));
	queue.push_front(std::pair<int, int>(start.first, start.second - (start.first * 2)));
	queue.push_front(std::pair<int, int>(start.first, start.second));

	return queue;
}

bool AISystem::check_player_position_Y(std::pair<int, int> location, std::pair<int, int> end) const{
	if ((location.second >= end.second - range) && (location.second <= end.second + range)) {
		return true;
	}
	return false;
}

bool AISystem::check_player_position_X(std::pair<int, int> location , std::pair<int, int> end) const{
	if ((location.first >= end.first - range) && (location.first <= end.first + range)) {
		return true;
	}
	return false;
}


void AISystem::best_first_search(EntityManager& em, PositionComponent& npc_xy) const{
	auto velocity = npc_xy.entity.get<VelocityComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();

	auto player_position = player_component.entity.get<PositionComponent>();
	auto player_drawable = player_component.entity.get<DrawableComponent>();//testing
	auto drawable = npc_xy.entity.get<DrawableComponent>();//testing

	std::pair< int, int> end(player_position->x, player_position->y); // end location
	std::pair<int, int> start(npc_xy.x, npc_xy.y); // start location

	std::list <std::pair< std::pair<int,int>,std::pair<int,int>>> path; // path to end location
	std::list <std::pair< int, int >> queue; // need to visited these positions

	queue = calculate_next_positions(start, end, queue);

	while (!queue.empty()) {
		std::pair<int, int> location = queue.front();
		queue.pop_front();

		if (path.size() == 0) {
			std::pair< std::pair<int, int>, std::pair<int, int>> next_value(start, location);
			path.push_back(next_value);
		}
		else {
			std::pair< std::pair<int, int>, std::pair<int, int>> next_value(path.back().second, location);
			path.push_back(next_value);
		}
	
		if (check_player_position_X(location, end) && check_player_position_Y(location, end)) {
			queue.clear();
		}
		else { 
			queue = calculate_next_positions(location, end, queue); 
		}
	}
	std::cout << "player: X: " << end.first << " Y: " << end.second << " Drawable X: " << player_drawable->texture->get_position().x << " Y: " << player_drawable->texture->get_position().y << std::endl;
	std::cout << "npc: X: " << start.first << " Y: " << start.second << " Drawable X: " << drawable->texture->get_position().x << " Y: " << drawable->texture->get_position().y << std::endl;
	auto direction = path.front();

	if (direction.first.first < direction.second.first) { 
		if (!check_player_position_X(direction.first, end)) velocity->x += 2;
	}
	else if(direction.first.first > direction.second.first){ 
		if(!check_player_position_X(direction.first, end)) velocity->x -= 2; 
	}
	if (direction.first.second > direction.second.second) { 
		if (!check_player_position_Y(direction.first, end)) velocity->y -= 2; 
	}
	else if(direction.first.second < direction.second.second) { 
		if (!check_player_position_Y(direction.first, end)) velocity->y += 2; 
	}
}

void AISystem::move_random(const Entity& entity, EntityManager& em) const{

	auto velocity = entity.get<VelocityComponent>();

	velocity->x += random_x(velocity);
	velocity->y += random_y(velocity);

}

void AISystem::run(EntityManager& em) const {
	auto vector = em.get_components_of_type<AIComponent>();
	auto player = em.get_entities_with_component<PlayerComponent>()[0];

	for (auto& element : vector) {
		if (check_health(em, element.get().entity)) {
			auto AI = element.get().entity.get<AIComponent>();
			auto xy = element.get().entity.get<PositionComponent>();
			switch (AI->_state)
			{
			case AIComponent::Fighting:
				best_first_search(em, *xy);
				break;
			case AIComponent::Fleeing:
				//TODO:implement Fleeing
				break;
			case AIComponent::Static:
				move_random(element.get().entity, em);
				break;
			default:
				break;
			}
		}
	}
}

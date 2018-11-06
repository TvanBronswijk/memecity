#include "AISystem.h"


std::string AISystem::SYSTEM_TYPE = "AISystem";

AISystem::AISystem(){
}

bool AISystem::check_health(EntityManager & em, Component*& element) {
	HealthComponent* health = dynamic_cast<HealthComponent*>(em.get_component_of_entity(element->entity_id, HealthComponent::COMPONENT_TYPE));
	if(health->_health <= 0) {
		std::cout << "i am dead!!!" << std::endl;
		return false;
	}
	return true;
}

inline int AISystem::random_x(VelocityComponent* velocity) {return (rand() % (2 - -1)) + -1;}
inline int AISystem::random_y(VelocityComponent* velocity) {return (rand() % (2 - -1)) + -1;}

std::list <std::pair< int, int >> AISystem::calculate_next_positions(std::pair< int, int >start , std::pair< int, int >end, std::list <std::pair< int, int >> queue) {
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

bool AISystem::check_player_position_Y(std::pair<int, int> location, std::pair<int, int> end) {
	if ((location.second >= end.second - range) && (location.second <= end.second + range)) {
		return true;
	}
	return false;
}

bool AISystem::check_player_position_X(std::pair<int, int> location , std::pair<int, int> end) {
	if ((location.first >= end.first - range) && (location.first <= end.first + range)) {
		return true;
	}
	return false;
}


void AISystem::best_first_search(EntityManager & em, PositionComponent* npc_xy) {
	VelocityComponent* velocity = dynamic_cast<VelocityComponent*>(em.get_component_of_entity(npc_xy->entity_id, VelocityComponent::COMPONENT_TYPE));
	auto player = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);

	DrawableComponent* drawable = dynamic_cast<DrawableComponent*>(em.get_component_of_entity(npc_xy->entity_id, DrawableComponent::COMPONENT_TYPE));//testing
	PositionComponent* player_position = nullptr;//testing
	DrawableComponent* player_drawable = nullptr;//testing

	for (auto & player : player) {
		player_position = dynamic_cast<PositionComponent*>(em.get_component_of_entity(player->id, PositionComponent::COMPONENT_TYPE));
		player_drawable = dynamic_cast<DrawableComponent*>(em.get_component_of_entity(player->id, DrawableComponent::COMPONENT_TYPE));
	}

	std::pair< int, int> end(player_position->x, player_position->y); // end location
	std::pair<int, int> start(npc_xy->x, npc_xy->y); // start location

	std::list <std::pair< std::pair<int,int>,std::pair<int,int>>> path; // path to end location
	std::list <std::pair< int, int >> queue; // need to visited these positions

	queue = calculate_next_positions(start, end, queue);

	while (!queue.empty()) {
		std::pair<int, int> location = queue.front(); // first location
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
	//std::cout << "player: X: " << end.first << " Y: " << end.second << " Drawable X: " << player_drawable->texture->get_position().x << " Y: " << player_drawable->texture->get_position().y << std::endl;
	//std::cout << "npc: X: " << start.first << " Y: " << start.second << " Drawable X: " << drawable->texture->get_position().x << " Y: " << drawable->texture->get_position().y << std::endl;
	}
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

void AISystem::move_random(int element, EntityManager& em) {

	VelocityComponent* velocity = (VelocityComponent*)em.get_component_of_entity(element, VelocityComponent::COMPONENT_TYPE);
	PositionComponent* xy = (PositionComponent*)em.get_component_of_entity(element, PositionComponent::COMPONENT_TYPE);

	velocity->x += random_x(velocity);
	velocity->y += random_y(velocity);

	int previousX = xy->x;
	int previousY = xy->y;


	//std::cout << "NPC has Placed with X: " << xy->x << "Y: " << xy->y << std::endl;
}

std::string AISystem::get_type() {
	return SYSTEM_TYPE;
}
void AISystem::run(EntityManager &em) {
	auto vector = em.get_components_of_type(AIComponent::COMPONENT_TYPE);
	auto player = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);

	for (auto & element : vector) {
		if (check_health(em, element)) {
			AIComponent* AI = (AIComponent*)element;
			PositionComponent* xy = dynamic_cast<PositionComponent*>(em.get_component_of_entity(element->entity_id, PositionComponent::COMPONENT_TYPE));
			switch (AI->_state)
			{
			case AIComponent::FIGHTING:
				best_first_search(em, xy);
				break;
			case AIComponent::FLEEING:
				break;
			case AIComponent::STATIC:
				move_random(element->entity_id, em);
				break;
			default:
				break;
			}
		}
	}
}
void AISystem::run(EntityManager &em, EventArgs& e) {
	/*
	 if(e.message == interaction){
		texture.showtext(interaction.smalltalk[rand]);
	 }
	*/
}
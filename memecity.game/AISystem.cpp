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

int AISystem::random_x(VelocityComponent* velocity) {
	return (rand() % (2 - -1)) + -1;
}

int AISystem::random_y(VelocityComponent* velocity) {
	return (rand() % (2 - -1)) + -1;
}
std::list <std::pair< int, int >> AISystem::calculate_next_positions(std::pair< int, int >start , std::pair< int, int >end) {
	std::list <std::pair< int, int >> next_positions;
	int x;
	int y;

	if (start.first < end.first) { x = 10; }
	else { x = -10;}
	if (start.second < end.second) { y = 10; }
	else { y = -10;}

	next_positions.push_back(std::pair<int, int>(start.first + x, start.second + y));
	next_positions.push_back(std::pair<int, int>(start.first - x, start.second + y));
	next_positions.push_back(std::pair<int, int>(start.first + x, start.second - y));
	next_positions.push_back(std::pair<int, int>(start.first - x, start.second - y));

	return next_positions;
}

bool AISystem::check_player_position_Y(std::pair<int, int> location, std::pair<int, int> end) {
	if ((location.second > end.second - 6) && (location.second < end.second + 5)) {
		return true;
	}
	return false;
}

bool AISystem::check_player_position_X(std::pair<int, int> location , std::pair<int, int> end) {
	if ((location.first > end.first - 6) && (location.first < end.first + 5)) {
		return true;
	}
	return false;
}


void AISystem::best_first_search(EntityManager & em, PositionComponent* npc_xy) {
	VelocityComponent* velocity = dynamic_cast<VelocityComponent*>(em.get_component_of_entity(npc_xy->entity_id, VelocityComponent::COMPONENT_TYPE));
	DrawableComponent* drawable = dynamic_cast<DrawableComponent*>(em.get_component_of_entity(npc_xy->entity_id, DrawableComponent::COMPONENT_TYPE));//testing
	auto player = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);
	PositionComponent* player_position = nullptr;
	DrawableComponent* player_drawable = nullptr;

	for (auto & player : player) {
		player_position = dynamic_cast<PositionComponent*>(em.get_component_of_entity(player->id, PositionComponent::COMPONENT_TYPE));
		player_drawable = dynamic_cast<DrawableComponent*>(em.get_component_of_entity(player->id, DrawableComponent::COMPONENT_TYPE));
	}

	std::pair< int, int> end(player_position->x, player_position->y);
	//list of all active boundingboxes.

	std::list <std::pair< std::pair<int,int>,std::pair<int,int>>> path;
	std::list <std::pair< int, int >> visited;
	std::list <std::pair< int, int >> queue;

	std::pair<int, int> start(npc_xy->x, npc_xy->y);
	queue.push_back(start);
	std::list <std::pair< int, int >>::iterator i;


		while (!queue.empty()) {
			start = queue.front();
			queue.pop_front();
			visited.push_back(start);
			std::list <std::pair< int, int >> next_positions = calculate_next_positions(start, end);
			/*for (//list of active boudingboxes) {*/
			std::pair<int,int> location = next_positions.front();
			// check if new location doenst hit the boundingbox
			std::pair< std::pair<int, int>, std::pair<int, int>> node(start, location);
			path.push_back(node);
			visited.push_back(location);

			//std::cout << "player: X: " << end.first << " Y: " << end.second << " Drawable X: " << player_drawable->texture->get_position().x << " Y: " << player_drawable->texture->get_position().y << std::endl;
			//std::cout << "npc: X: " << start.first << " Y: " << start.second << " Drawable X: " << drawable->texture->get_position().x << " Y: " << drawable->texture->get_position().y << std::endl;
			if(!check_player_position_X(location, end) && !check_player_position_Y(location,end)){
				queue.push_back(location);
			}
			//}

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
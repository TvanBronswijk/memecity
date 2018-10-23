#include "AISystem.h"


std::string AISystem::SYSTEM_TYPE = "AISystem";

AISystem::AISystem(){
}

void AISystem::check_health() {
	/*if (HC.health = < 0) {
		texture.animate(dead);
	}*/
}

int AISystem::random_x(VelocityComponent* velocity) {
	return (rand() % (2 - -1)) + -1;
}

int AISystem::random_y(VelocityComponent* velocity) {
	return (rand() % (2 - -1)) + -1;
}

void AISystem::move_random(int element, EntityManager& em) {

	VelocityComponent* velocity = (VelocityComponent*)em.get_component_of_entity(element, VelocityComponent::COMPONENT_TYPE);
	PositionComponent* xy = (PositionComponent*)em.get_component_of_entity(element, PositionComponent::COMPONENT_TYPE);

	velocity->x += random_x(velocity);
	velocity->y += random_y(velocity);

	int previousX = xy->x;
	int previousY = xy->y;


	std::cout << "NPC has Placed with X: " << xy->x << "Y: " << xy->y << std::endl;
}

std::string AISystem::get_type() {
	return SYSTEM_TYPE;
}
void AISystem::run(EntityManager &em) {
	auto vector = em.get_components_of_type(AIComponent::COMPONENT_TYPE);

	for (auto & element : vector) {
		AIComponent* AI = (AIComponent*)element;
		switch (AI->_state)
		{

		case AIComponent::FIGHTING:
			//check where player is on de map
			//move in correct direction
			/*if (player.x > (xy.x - (range / 2)) && player.y < (xy.y + (range / 2))) {
				texture.animate(fight);
				player.health = -damage;
			}*/
			break;
		case AIComponent::FLEEING:
			//check where player is on de map
			//move in oposite direction
			break;
		case AIComponent::STATIC:
			move_random(element->entity_id , em);
			break;
		default:
			break;
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
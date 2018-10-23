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
	return velocity->x = (rand() % (2 - -1)) + -1;
}

int AISystem::random_y(VelocityComponent* velocity) {
	return velocity->y = (rand() % (2 - -1)) + -1;
}

void AISystem::move_sprites() {
	/*
if(previousY > xy->y_position){
	texture.animate(up);
}
else if(previousY < xy->y_position){
	texture.animate(down);
}
else if(previousX < xy->x_position){
	texture.animate(left);
}
else if(previousX > xy->x_position){
	texture.animate(right);
}else{
	texture.animate(hold);
}*/
}

void AISystem::move_random(Entity* element, EntityManager em) {

	VelocityComponent* velocity = (VelocityComponent*)em.get_component_of_entity(element->id, "VelocityComponent");
	PositionComponent* xy = (PositionComponent*)em.get_component_of_entity(element->id, "PositionComponent");

	velocity->x += random_x(velocity);
	velocity->y += random_y(velocity);

	int previousX = xy->x;
	int previousY = xy->y;


	std::cout << "NPC has Placed with X: " << xy->x << "Y: " << xy->y << std::endl;
}

bool AISystem::is_on_event(Event *e) {
	return false;
}

std::string AISystem::get_type() {
	return SYSTEM_TYPE;
}
void AISystem::run(EntityManager &em) {
	auto vector = em.get_entities_with_component(AIComponent::COMPONENT_TYPE);

	for (auto & element : vector) {
		AIComponent* AI = (AIComponent*)em.get_component_of_entity(element->id, AIComponent::COMPONENT_TYPE);
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
			move_random(element , em);
			break;
		default:
			break;
		}
		move_sprites();
	}
}
void AISystem::run(EntityManager &em, Event *e) {
	/*
	 if(e.message == interaction){
		texture.showtext(interaction.smalltalk[rand]);
	 }
	*/
}
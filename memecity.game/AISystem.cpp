#include "AISystem.h"


std::string AISystem::COMPONENT_TYPE = "AISystem";

AISystem::AISystem(){
}

bool AISystem::is_on_event(Event *e) {
	return false;
}


std::string AISystem::get_type() {
	return COMPONENT_TYPE;
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
			MoveRandom(element , em);
			break;
		default:
			break;
		}
		MoveSprites();
	}
}
void AISystem::run(EntityManager &em, Event *e) {
	/*
	 if(e.message == interaction){
		texture.showtext(interaction.smalltalk[rand]);
	 }
	*/
}

void MoveSprites() {
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

void MoveRandom(Entity* element , EntityManager em) {

	VelocityComponent* velocity = (VelocityComponent*)em.get_component_of_entity(element->id, "VelocityComponent");
	PositionComponent* xy = (PositionComponent*)em.get_component_of_entity(element->id, "PositionComponent");

	velocity->x += RandomX(velocity);
	velocity->y += RandomY(velocity);

	int previousX = xy->x_position;
	int previousY = xy->y_position;

	xy->x_position += velocity->x;
	xy->y_position += velocity->y;


	std::cout << "NPC has Placed with X: " << xy->x_position << "Y: " << xy->y_position << std::endl;
}

void CheckHealth() {
	/*if (HC.health = < 0) {
		texture.animate(dead);
	}*/
}

int RandomX(VelocityComponent* velocity) {
	return velocity->x = (rand() % (2 - -1)) + -1;
}

int RandomY(VelocityComponent* velocity) {
	return velocity->y = (rand() % (2 - -1)) + -1;
}
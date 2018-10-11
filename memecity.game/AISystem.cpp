#include "AISystem.h"


int RandomX() {
	return rand() % -2 + 2;
}

int RandomY() {
	return rand() % -2 + 2;
}

std::string AiSystem::get_type() {
	return "AISystem";
}
void AiSystem::run(EntityManager &em) {
	AIComponent AI;
	VelocityComponent VC;
	PositionComponent PC;

	int x = RandomX();
	int y = RandomY();

	PC.x_position = PC.x_position + x;
	PC.y_position = PC.y_position + y;


}
void AiSystem::run(EntityManager &em, Event &e) {

}
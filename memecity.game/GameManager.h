#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"
#include "InputSystem.h"
#include "VelocityComponent.h"
#include "InputComponent.h"

class GameManager : public MemeEngine 
{
private:
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> text;
	InputSystem *input_system;
	std::unique_ptr<EntityManager> entity_manager;
	VelocityComponent *velocity_component;
	InputComponent *input_component;
	Entity* entity;

protected:
	bool init() override;
	void handle() override;
};


#endif
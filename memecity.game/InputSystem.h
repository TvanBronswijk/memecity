#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include "../memecity.engine/InputManager.h"
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"


class InputSystem : public System
{
	static const std::string SYSTEM_TYPE;
private:
	std::weak_ptr<InputManager> input_manager;
public:
	InputSystem(std::weak_ptr<InputManager> input_manager);
	void run(EntityManager& em) override;
	std::string get_type() const override; 
	void run(EntityManager& em, EventArgs& e) override;
};

#endif
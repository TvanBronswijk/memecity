#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include "InputManager.h"
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"

class InputSystem : public System
{
	static std::string SYSTEM_TYPE;
private:
	std::weak_ptr<InputManager> input_manager;
public:
	InputSystem(std::weak_ptr<InputManager> input_manager);
	bool is_on_event(Event *e) override;
	void run(EntityManager& em) override;
	std::string get_type() override;
	void run(EntityManager &em, Event *e) override;
};

#endif
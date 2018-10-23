#pragma once
#include "../memecity.engine.ecs/System.h"

class Event;

class ExpSystem: public System
{
public:
	ExpSystem();
	~ExpSystem();
	std::string get_type() override;
	void run(EntityManager& em) override;
	void run(EntityManager& em, EventArgs& e) override;
};


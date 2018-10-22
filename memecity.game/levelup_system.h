#pragma once
#include "../memecity.engine.ecs/System.h"

class levelup_system: public System
{
public:
	levelup_system();
	~levelup_system();


	bool is_on_event(Event* e) override;
	std::string get_type() override;
	void run(EntityManager& em) override;
	void run(EntityManager& em, Event* e) override;
};


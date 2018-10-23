#ifndef _EXP_SYSTEM_H
#define _EXP_SYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include <string>
#include "ExpComponent.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "StatsComponent.h"
#include "Event.h"
#include "ExpEventArgs.h"


class ExpSystem: public System
{
	static std::string SYSTEM_TYPE;
public:
	
	ExpSystem();
	~ExpSystem();
	std::string get_type() override;
	void run(EntityManager& em) override;
	void run(EntityManager& em, EventArgs& e) override;
};

#endif
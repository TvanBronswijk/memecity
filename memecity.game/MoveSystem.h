#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"

class MoveSystem : public System
{
public:

	void run(EntityManager& em) override;

};

#endif
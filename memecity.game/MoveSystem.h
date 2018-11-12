#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include <ECS.h>
class MoveSystem : public ecs::System
{
public:
	void run(ecs::EntityManager& em) const override;
};
#endif

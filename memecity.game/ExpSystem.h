#ifndef _EXP_SYSTEM_H
#define _EXP_SYSTEM_H
#include <ECS.h>
class ExpSystem: public ecs::System
{
public:
	void run(ecs::EntityManager& em) const override;
	void on_exp_gain(ecs::EntityManager& em, int exp) const;
};
#endif

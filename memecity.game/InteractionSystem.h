#include <ECS.h>
#include "InteractionEventArgs.h"
#include "MultimediaManager.h"

class InteractionSystem : public ecs::System {

public:
	void run(ecs::EntityManager& em) const override;
	void interact(ecs::EntityManager& em, InteractionEventArgs args);
};

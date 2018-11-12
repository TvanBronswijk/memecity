#include <ECS.h>
#include "InteractionEventArgs.h"
#include "Engine\MultimediaManager.h"

class InteractionSystem : public memecity::engine::ecs::System {

public:
	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_interact(memecity::engine::ecs::EntityManager& em, InteractionEventArgs args);
};

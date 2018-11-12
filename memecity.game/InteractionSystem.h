#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "../memecity.engine/MultimediaManager.h"
#include "InteractionEventArgs.h"

class InteractionSystem : public ecs::System {

private:
	MultimediaManager &multimedia_manager;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	InteractionSystem(MultimediaManager& multimedia_manager);
	void run(ecs::EntityManager& em) const override;
	void interact(ecs::EntityManager& em, InteractionEventArgs args);
	ecs::system_typetoken get_type_token() const override { return InteractionSystem::SYSTEM_TYPE; }
};

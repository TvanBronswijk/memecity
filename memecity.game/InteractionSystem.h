#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include <cstdlib>
#include "InteractionEventArgs.h"
#include "PositionComponent.h"
#include "interactionComponent.h"
#include "../memecity.engine/MultimediaManager.h"
#include "DrawableComponent.h"

class InteractionSystem : public ecs::System {

private:
	MultimediaManager &multimedia_manager;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	InteractionSystem(MultimediaManager& multimedia_manager);
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return InteractionSystem::SYSTEM_TYPE; }
};

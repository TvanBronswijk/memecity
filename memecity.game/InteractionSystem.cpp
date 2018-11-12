#include "InteractionSystem.h"

#include "PositionComponent.h"
#include "interactionComponent.h"
#include "DrawableComponent.h"

using namespace ecs;

void InteractionSystem::run(EntityManager &em) const {

}

void InteractionSystem::interact(EntityManager &em, InteractionEventArgs args) {
	auto xy = args.source.get<PositionComponent>();
	auto interaction = args.source.get<InteractionComponent>();

	if (interaction != nullptr) {
		//TODO:: make texture with text
		std::cout << "NPC :" << args.source.id << "is saying to you: " << interaction->_smallTalk[1] << std::endl;

	}

}
#include "InteractionSystem.h"

#include "PositionComponent.h"
#include "interactionComponent.h"
#include "DrawableComponent.h"

using namespace ecs;

system_typetoken InteractionSystem::SYSTEM_TYPE = "InteractionSystem";

InteractionSystem::InteractionSystem(MultimediaManager &multimedia_manager) : multimedia_manager(multimedia_manager) {
}

void InteractionSystem::run(EntityManager &em) const {

}

void InteractionSystem::interact(EntityManager &em, InteractionEventArgs args) {
	auto xy = em.get_component_of_entity<PositionComponent>(args.source.id, PositionComponent::COMPONENT_TYPE);
	auto interaction = em.get_component_of_entity<InteractionComponent>(args.source.id, InteractionComponent::COMPONENT_TYPE);

	if (interaction != nullptr) {
		//TODO:: make texture with text
		std::cout << "NPC :" << args.source.id << "is saying to you: " << interaction->_smallTalk[1] << std::endl;

	}

}
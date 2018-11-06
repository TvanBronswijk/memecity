#include "InteractionSystem.h"


std::string InteractionSystem::SYSTEM_TYPE = "InteractionSystem";

InteractionSystem::InteractionSystem(std::weak_ptr<MultimediaManager> multi_media) {
	this->multimedia_manager = multi_media;
}

std::string InteractionSystem::get_type() {
	return SYSTEM_TYPE;
}
void InteractionSystem::run(EntityManager &em) {

}
void InteractionSystem::run(EntityManager &em, EventArgs& e) {

	const auto interaction_event_args = static_cast<InteractionEventArgs&>(e);
	auto xy = em.get_component_of_entity(interaction_event_args.source_entity_id, PositionComponent::COMPONENT_TYPE);
	auto interaction = dynamic_cast<InteractionComponent*>(em.get_component_of_entity(interaction_event_args.source_entity_id, InteractionComponent::COMPONENT_TYPE));

	if (interaction != nullptr) {
		//auto text_texture = multimedia_manager.lock()->get_text_texture(interaction->_smallTalk[1], "Blazed.ttf", 10, { 0,0,0 });
		std::cout << "NPC :" << interaction_event_args.source_entity_id << "is saying to you: " << interaction->_smallTalk[1] << std::endl;

	}

}
#include "InteractionSystem.h"

using namespace memecity::engine::ecs;

void InteractionSystem::run(EntityManager &em) const {
	auto vector = em.get_components_of_type<InteractionComponent>();
	for (auto& component : vector) {
		auto text_texture = &component.get().get_texture();
		if (text_texture->get_text() != " ") {
			if (component.get().timer++ > 100) {
				auto npc_interaciton_texture = multimedia_manager.get_text_texture(" ", "Minecraftia-Regular.ttf", 14, { 255,255,255 });
				npc_interaciton_texture->set_position({ 0, -35 });
				npc_interaciton_texture->set_parent(text_texture->get_parent());
				component.get().texture = std::move(npc_interaciton_texture);
				component.get().timer = 0;
			}
		}
	}
}

void InteractionSystem::on_interact(EntityManager &em, InteractionEventArgs args) {
	auto health = args.source.get<HealthComponent>();
	if (health->health > 0) {
		auto xy = args.source.get<PositionComponent>();
		auto interaction = args.source.get<InteractionComponent>();

		if (interaction != nullptr) {
			auto text_texture = &interaction->get_texture();
			auto npc_interaciton_texture = multimedia_manager.get_text_texture(interaction->smallTalk[1], "Minecraftia-Regular.ttf", 14, { 255,255,255 });
			npc_interaciton_texture->set_position({ 0, -35 });
			npc_interaciton_texture->set_parent(text_texture->get_parent());
			interaction->texture = std::move(npc_interaciton_texture);

		}
	}

}

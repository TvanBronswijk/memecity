#include "InteractionSystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "..\..\Assets.h"

using namespace memecity::engine::ecs;

void InteractionSystem::run(EntityManager &em, float dt) const {
	auto vector = em.get_components_of_type<InteractionComponent>();
	for (auto& component : vector) {
		auto text_texture = &component.get().get_texture();
		if (text_texture->get_text() != " ") {
			auto ai = component.get().entity().get<AIComponent>();
			if (ai != nullptr) {
				if (component.get().start_time > 1) {
					auto npc_interaciton_texture = this->_context->get_multimedia_manager().get_text(" ", 14);
					npc_interaciton_texture->set_position({ 0, -35 });
					npc_interaciton_texture->set_parent(text_texture->get_parent());
					component.get().texture = std::move(npc_interaciton_texture);
					
					auto npc_name_texture = this->_context->get_multimedia_manager().get_text(ai->name, 14);
					npc_name_texture->set_position({ 0, -35 });
					npc_name_texture->set_parent(ai->texture->get_parent());
					ai->texture = std::move(npc_name_texture);
					
					component.get().start_time = 0;
				}
			}
			else {
				if (component.get().start_time > (component.get().text.size() * 2)) {
						auto npc_interaciton_texture = this->_context->get_multimedia_manager().get_text(" ", 14);
						
						npc_interaciton_texture->set_position({ 0, -35 });
						npc_interaciton_texture->set_parent(text_texture->get_parent());
						component.get().texture = std::move(npc_interaciton_texture);
						component.get().start_time = 0;
						component.get().current_text_int = 0;
				}
			}
			component.get().start_time += _context->get_timer().get_delta_time();
		}
	}
}

void InteractionSystem::on_interact(EntityManager &em, InteractionEventArgs args) {
	auto interaction = args.source.get<InteractionComponent>();

	auto text_texture = &interaction->get_texture();

	std::string text = " ";

	if (args.source.get<AIComponent>() != nullptr) {
		auto health = args.source.get<HealthComponent>();
		if (health->health > 0) {
			text = interaction->text[(rand() % (interaction->text.size()))];

			auto npc_name_texture = this->_context->get_multimedia_manager().get_text(" ", 14);
			npc_name_texture->set_position({ 0, -35 });
			npc_name_texture->set_parent(text_texture->get_parent());
			args.source.get<AIComponent>()->texture = std::move(npc_name_texture);
		}
	}
	else {
		if (interaction->get_texture().get_text() != " ") {
			interaction->current_text_int++;
			if (interaction->current_text_int <= interaction->text.size()-1) {
				text = interaction->text[interaction->current_text_int];
			}
		}else
		text = interaction->text[0];
	}

	auto npc_interaciton_texture = _context->get_multimedia_manager().get_text(assets::fonts::DEFAULT_FONT, text, 14, { 255,255,255 });
	npc_interaciton_texture->set_position({ 0, -35 });
	npc_interaciton_texture->set_parent(text_texture->get_parent());
	interaction->texture = std::move(npc_interaciton_texture);


	quest_event.fire(em, { &args.source, nullptr });

}

void InteractionSystem::on_pickpocket(EntityManager &em, FaultyPickpocketEventArgs args) {
	auto interaction = args.ai.get<InteractionComponent>();

	auto text_texture = &interaction->get_texture();

	auto npc_name_texture = this->_context->get_multimedia_manager().get_text(" ", 14);
	npc_name_texture->set_position({ 0, -35 });
	npc_name_texture->set_parent(text_texture->get_parent());
	args.ai.get<AIComponent>()->texture = std::move(npc_name_texture);

	auto npc_interaciton_texture = _context->get_multimedia_manager().get_text(assets::fonts::DEFAULT_FONT, args.text, 14, { 255,255,255 });
	npc_interaciton_texture->set_position({ 0, -35 });
	npc_interaciton_texture->set_parent(text_texture->get_parent());
	interaction->texture = std::move(npc_interaciton_texture);

	interaction->start_time = 0;
}

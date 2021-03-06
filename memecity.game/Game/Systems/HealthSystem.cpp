#include "HealthSystem.h"
#include "../States/GameOverState.h"
#include "..\..\Assets.h"

using namespace memecity::engine::ecs;

void HealthSystem::run(EntityManager& em, float dt) const {}

void HealthSystem::on_damage(EntityManager& em, std::reference_wrapper<const Entity> entity) {
	auto health_target = entity.get().get<HealthComponent>();
	auto AI = entity.get().get<AIComponent>();
	auto stats_target = entity.get().get<StatsComponent>();

	std::string hp = "HP: ";
	hp += std::to_string(health_target->health);
	hp += "/";
	hp += std::to_string(health_target->maxhealth);


	if (health_target->health > (health_target->maxhealth / 2)) {
		auto text_health_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&health_target->get_texture());
		auto target_health_texture = _context->get_multimedia_manager().get_text(assets::fonts::DEFAULT_FONT, hp, 10, { 34,139,34 });
		target_health_texture->set_position({ 0, -20 });
		target_health_texture->set_parent(text_health_texture->get_parent());
		health_target->texture = std::move(target_health_texture);
	}
	else if (health_target->health <= (health_target->maxhealth / 2) && health_target->health > 0) {
		auto text_health_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&health_target->get_texture());
		auto target_health_texture = _context->get_multimedia_manager().get_text(assets::fonts::DEFAULT_FONT, hp, 10, { 255,140,0 });
		target_health_texture->set_position({ 0, -20 });
		target_health_texture->set_parent(text_health_texture->get_parent());
		health_target->texture = std::move(target_health_texture);
	}
	else {
		auto text_health_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&health_target->get_texture());
		auto target_health_texture = _context->get_multimedia_manager().get_text(assets::fonts::DEFAULT_FONT, hp, 10, { 220,20,60 });
		target_health_texture->set_position({ 0, -20 });
		target_health_texture->set_parent(text_health_texture->get_parent());
		health_target->texture = std::move(target_health_texture);
	}


	if (health_target->health < (health_target->maxhealth / 10)) {
		if ((rand() % stats_target->strength) < 5)
			if (AI->state != Ai_State::Fleeing)
				AI->state = Ai_State::Fleeing;
	}
}


#include "NPCGenerator.h"
#include "..\..\Components.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "..\..\..\Assets.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

namespace generate {
	int NPCGenerator::random_int(int max) {
		srand(time(NULL));
		if (max <= 0) {
			return 0;
		}
		return (rand() % max);
	}

	const memecity::engine::ecs::Entity& NPCGenerator::generate(int maxlevel, float x, float y) {
		this->level = rand() % maxlevel + 1;
		this->x = x;
		this->y = y;

		int points = level * 5;
		int strength_points = random_int(points) + 5;
		strength += strength_points;
		points -= strength_points;
		int perception_points = random_int(points) + 5;
		perception += perception_points;
		points -= perception_points;
		int endurance_points = random_int(points) + 5;
		endurance += endurance_points;
		points -= endurance_points;
		int charisma_points = random_int(points) + 5;
		charisma += charisma_points;
		points -= charisma_points;
		int intelligence_points = random_int(points) + 5;
		intelligence += intelligence_points;
		points -= intelligence_points;
		int agility_points = random_int(points) + 5;
		agility += agility_points;
		points -= agility_points;
		luck += points + 5;

		health = ((strength * 5) + (endurance * 3) + (agility * 2) + 50);

		std::string hp = "HP: ";
		hp += std::to_string(health);
		hp += "/";
		hp += std::to_string(health);

		auto animation_texture = multimedia_manager.get_texture(assets::spritesheets::HUMAN_MALE_1, 0, 0, 48, 48, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
		animation_texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });

		auto health_texture = multimedia_manager.get_text(hp, 10, { 34,139,34 });
		health_texture->set_position({ 0, -20 });
		health_texture->set_parent(animation_texture.get());

		auto interaction_texture = multimedia_manager.get_text(" ", 14);
		interaction_texture->set_position({ 0, -35 });
		interaction_texture->set_parent(animation_texture.get());

		auto& npc = builder::EntityBuilder(entity_manager)
			.create_entity("npc")
			.with_component<BaseComponent>(std::move(animation_texture), x, y, 48.0f, 48.0f)
			.with_component<AIComponent>()
			.with_component<VelocityComponent>()
			.with_component<LevelComponent>(level)
			.with_component<StatsComponent>(strength, perception, endurance, charisma, intelligence, agility, luck)
			.with_component<HealthComponent>(health, std::move(health_texture))
			.with_component<InteractionComponent>(std::move(interaction_texture))
			.with_component<AnimationComponent>()
			.get();

		return npc;
	}
}

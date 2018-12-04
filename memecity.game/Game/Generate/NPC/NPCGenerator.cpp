#include "NPCGenerator.h"
#include "..\..\Components.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../../Enum/AIStates.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

namespace generate {
	int NPCGenerator::random_int(int max) {
		srand(time(NULL));
		if (max <= 0 || 5 > max) {
			return 5;
		}
		return (5 + (rand() % (max)));
	}

	const memecity::engine::ecs::Entity& NPCGenerator::generate_random_npc(int maxlevel, float x, float y) {
		this->name = "rick";
		this->level = rand() % maxlevel + 1;
		this->x = x;
		this->y = y;

		int points = level * 5;
		int strength_points = random_int(points);
		strength += strength_points;
		points -= strength_points;
		int perception_points = random_int(points);
		perception += perception_points;
		points -= perception_points;
		int endurance_points = random_int(points);
		endurance += endurance_points;
		points -= endurance_points;
		int charisma_points = random_int(points);
		charisma += charisma_points;
		points -= charisma_points;
		int intelligence_points = random_int(points);
		intelligence += intelligence_points;
		points -= intelligence_points;
		int agility_points = random_int(points);
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

		std::string font = "Minecraftia-Regular.ttf";
		auto health_texture = multimedia_manager.get_text(font, hp, 10, { 34,139,34 });
		health_texture->set_position({ 0, -20 });
		health_texture->set_parent(animation_texture.get());

		auto name_texture = multimedia_manager.get_text(font, this->name, 14, { 255,255,255 });
		name_texture->set_position({ 0, -35 });
		name_texture->set_parent(animation_texture.get());

		auto interaction_texture = multimedia_manager.get_text(" ", 14);
		interaction_texture->set_position({ 0, -800 });
		interaction_texture->set_parent(animation_texture.get());

		auto& npc = builder::EntityBuilder(entity_manager)
			.create_entity()
			.with_component<AIComponent>(State::Idle,this->name,std::move(name_texture))
			.with_component<VelocityComponent>()
			.with_component<PositionComponent>(x, y)
			.with_component<LevelComponent>(level)
			.with_component<StatsComponent>(strength, perception, endurance, charisma, intelligence, agility, luck)
			.with_component<DrawableComponent>(std::move(animation_texture))//body of npc
			.with_component<HealthComponent>(health, std::move(health_texture))
			.with_component<InteractionComponent>(createInteractionStrings(), std::move(interaction_texture))
			.with_component<AnimationComponent>()
			.with_component<ColliderComponent>(48.0f, 48.0f)
			.get();

		return npc;
	}


	const memecity::engine::ecs::Entity& NPCGenerator::generate_npc(
		int level, float x, float y, int strength, int perception,
		int endurance, int charisma, int intelligence, int agility, 
		int luck, int health, std::string name,
		std::unique_ptr<memecity::engine::texture::Texture> animation_texture, 
		std::unique_ptr<memecity::engine::texture::TextTexture> health_texture,
		std::unique_ptr<memecity::engine::texture::TextTexture> interaction_texture,
		std::unique_ptr<memecity::engine::texture::TextTexture> name_texture) {

		auto& npc = builder::EntityBuilder(entity_manager)
			.create_entity()
			.with_component<AIComponent>(std::move(name_texture))
			.with_component<VelocityComponent>()
			.with_component<PositionComponent>(x, y)
			.with_component<LevelComponent>(level)
			.with_component<StatsComponent>(strength, perception, endurance, charisma, intelligence, agility, luck)
			.with_component<DrawableComponent>(std::move(animation_texture))//body of npc
			.with_component<HealthComponent>(health, std::move(health_texture))
			.with_component<InteractionComponent>(std::move(interaction_texture))
			.with_component<AnimationComponent>()
			.with_component<ColliderComponent>(48.0f, 48.0f)
			.get();

		return npc;

	}

	const memecity::engine::ecs::Entity& NPCGenerator::generate_quest_npc(std::string name, assets::Asset asset) {
		if (quest_npcs.find(name) != quest_npcs.end()) {
			return *quest_npcs.find(name)->second;
		}
		else {
			auto animation_texture = multimedia_manager.get_texture(asset, 0, 0, 48, 48, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
			animation_texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });

			std::string font = "Minecraftia-Regular.ttf";
			auto name_texture = multimedia_manager.get_text(font, name, 14, { 255,255,255 });
			name_texture->set_position({ 0, -35 });
			name_texture->set_parent(animation_texture.get());

			auto interaction_texture = multimedia_manager.get_text(" ", 14);
			interaction_texture->set_position({ 0, -800 });
			interaction_texture->set_parent(animation_texture.get());


			auto& quest_npc = builder::EntityBuilder(entity_manager)
				.create_entity()
				.with_component<QuestAIComponent>(name, std::move(name_texture))
				.with_component<PositionComponent>(0, 0)
				.with_component<DrawableComponent>(std::move(animation_texture))//body of npc
				.with_component<InteractionComponent>(std::move(interaction_texture))
				.with_component<ColliderComponent>(48.0f, 48.0f)
				.get();

			quest_npcs.insert(std::pair<std::string,const memecity::engine::ecs::Entity*>(name, &quest_npc));

			return quest_npc;
		}
	}

	std::vector<std::string> NPCGenerator::createInteractionStrings() {
		std::vector<std::string> interaction;

		int random = rand() % 2;

		switch (random) {
		case 0 :
			interaction.emplace_back("I'm very busy now");
			interaction.emplace_back("Sorry, i can't talk now.");
			interaction.emplace_back("Get out the way!");
			break;
		case 1:
			interaction.emplace_back("Hello Stranger!");
			interaction.emplace_back("What a nice wheater isn't it?");
			interaction.emplace_back("How are you sure?");
			break;
		case 2:
			interaction.emplace_back("Do I know you?");
			interaction.emplace_back("Where are you going?");
			interaction.emplace_back("I want to buy a onesie… but know it won’t suit me.");
			break;
		}
		return interaction;
	}

}

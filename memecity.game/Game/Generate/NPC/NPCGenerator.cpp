#include "NPCGenerator.h"
#include "../../Components.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../../../Assets.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

namespace generate {
	int NPCGenerator::random_int(int max) {
		return (rand() % (max + 1));
	}


	const memecity::engine::ecs::Entity& NPCGenerator::generate_police_npc(float x, float y) {
		std::string name = "Handhaving";
		int level = rand() % 1;
		//TODO:: change to map level
		int range_of_fighting = rand() % 30 + min_fighting_range;
		int movement_speed = rand() % 40 + min_movement_speed;
		int exp = rand() % 10 + 25;
		int blikcoins = rand() % (level * 5 + 1) + 5;

		int strength = 5 + level;
		int perception = 5 + level;
		int endurance = 5 + level;
		int charisma = 5 + level;
		int intelligence = 5 + level;
		int agility = 5 + level;
		int luck = 5 + level;

		int health = ((strength * 5) + (endurance * 3) + (agility * 2) + 50);

		std::string hp = "HP: ";
		hp += std::to_string(health);
		hp += "/";
		hp += std::to_string(health);

		return generate_npc(
			x, y, 48.0f, 48.0f, exp, range_of_fighting, movement_speed,blikcoins,
			strength, perception, endurance, charisma, intelligence, agility, luck,
			name, Ai_State::Roaming, {}, level,
			assets::spritesheets::HUMAN_MALE_1);
	}
	const memecity::engine::ecs::Entity& NPCGenerator::generate_civilian_npc(float x, float y) {
		std::string name = get_random_name();
		int level = 1;
		int range_of_fighting = min_fighting_range;
		int movement_speed = rand() % min_movement_speed;
		int exp = 10;
		int blikcoins = rand() % (level * 10 + 1) + 10;

		int health = 100;

		std::string hp = "HP: ";
		hp += std::to_string(health);
		hp += "/";
		hp += std::to_string(health);

		return generate_npc(
			x, y, 48.0f, 48.0f, exp, range_of_fighting, movement_speed,blikcoins,
			5, 5, 5, 5, 5, 5, 5,
			name, Ai_State::Roaming, {}, level,
			assets::spritesheets::HUMAN_MALE_1);
	}

	//random generator
	const memecity::engine::ecs::Entity& NPCGenerator::generate_random_npc(float x, float y) {
		std::string name = "random";
		int level = 1;
		int range_of_fighting = rand() % 30 + min_fighting_range;
		int movement_speed = rand() % 40 + min_movement_speed;
		int exp = rand() % 10 + 10;
		int blikcoins = rand() % (level * 10 + 1) + 10;

		int points = level * 5;
		int strength_points = random_int(points);
		int strength = strength_points + min_base_points;
		points -= strength_points;
		int perception_points = random_int(points);
		int perception = perception_points + min_base_points;
		points -= perception_points;
		int endurance_points = random_int(points);
		int endurance = endurance_points + min_base_points;
		points -= endurance_points;
		int charisma_points = random_int(points);
		int charisma = charisma_points + min_base_points;
		points -= charisma_points;
		int intelligence_points = random_int(points);
		int intelligence = intelligence_points + min_base_points;
		points -= intelligence_points;
		int agility_points = random_int(points);
		int agility = agility_points + min_base_points;
		points -= agility_points;
		int luck = points + min_base_points;

		return generate_npc(
			x, y, 48.0f, 48.0f, exp, range_of_fighting, movement_speed,blikcoins,
			strength, perception, endurance, charisma,intelligence, agility, luck, 
			name, Ai_State::Roaming, {}, level,
			assets::spritesheets::HUMAN_MALE_1);
	}

	//base generator
	const memecity::engine::ecs::Entity& NPCGenerator::generate_npc(
		float x, float y, float width,float height, int exp, int range_of_fighting, float movement_speed, int blikcoins,
		int strength, int perception, int endurance, int charisma,int intelligence, int agility, int luck, 
		std::string name, Ai_State state, std::vector<std::string>interaction, int level,
		assets::Asset animation_character){

		int health = ((strength * 5) + (endurance * 3) + (agility * 2) + 50);

		std::string hp = "HP: ";
		hp += std::to_string(health);
		hp += "/";
		hp += std::to_string(health);
		
		auto animation_texture = multimedia_manager.get_texture(animation_character, 0, 0, width, height, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
		animation_texture->set_position({ 0, 0});

		std::string font = assets::fonts::DEFAULT_FONT;
		auto health_texture = multimedia_manager.get_text(font, hp, 10, { 34,139,34 });
		health_texture->set_position({ 0, -20 });
		health_texture->set_parent(animation_texture.get());

		auto name_texture = multimedia_manager.get_text(font, name, 14, { 255,255,255 });
		name_texture->set_position({ 0, -35 });
		name_texture->set_parent(animation_texture.get());

		auto interaction_texture = multimedia_manager.get_text(" ", 14);
		interaction_texture->set_position({ 0, -35 });
		interaction_texture->set_parent(animation_texture.get());

		const char* entity_name = name.c_str();
		auto& builder = entity_manager.create_entity(entity_name)
			.with_component<BaseComponent>(std::move(animation_texture), x, y, width, height)
			.with_component<AIComponent>(state, name, exp, range_of_fighting, movement_speed,blikcoins, std::move(name_texture))
			.with_component<VelocityComponent>()
			.with_component<AnimationComponent>()
			.with_component<LevelComponent>(level)
			.with_component<StatsComponent>(strength, perception, endurance, charisma, intelligence, agility, luck)
			.with_component<HealthComponent>(health, std::move(health_texture));

		if (interaction.empty()) {
			builder.with_component<InteractionComponent>(create_interaction_strings(), std::move(interaction_texture));
		}
		else {
			builder.with_component<InteractionComponent>(interaction, std::move(interaction_texture));
		}

		auto base_component = builder.get().get<BaseComponent>();
		builder.with_component<ColliderComponent>(BoundaryRectangle(base_component->location.x, base_component->location.y, base_component->w, base_component->h));

		return builder.get();

	}

	//get random interaction
	std::vector<std::string> NPCGenerator::create_interaction_strings() {
		std::vector<std::string> interaction;

		int random = rand() % 2;

		switch (random) {
		case 0:
			interaction.emplace_back("I'm very busy now");
			interaction.emplace_back("Sorry, i can't talk now.");
			interaction.emplace_back("Get out the way!");
			break;
		case 1:
			interaction.emplace_back("Hello Stranger!");
			interaction.emplace_back("What a nice weather isn't it?");
			interaction.emplace_back("How are you Sir?");
			break;
		case 2:
			interaction.emplace_back("Do I know you?");
			interaction.emplace_back("Where are you going?");
			interaction.emplace_back("I want to buy a onesie… but know it won’t suit me.");
			break;
		}
		return interaction;
	}

	std::string NPCGenerator::get_random_name() {
		//both vectors need to be the same size;
		int number = rand() % (this->names_boys.size() -1);
		int gender = rand() % 100;
		if (gender < 50) {
			return this->names_boys.at(number);
		}
		else {
			return this->names_girls.at(number);
		}


	}

	//Quests_npcs
	const memecity::engine::ecs::Entity& NPCGenerator::generate_quest_npc(std::string name, int x, int y, assets::Asset asset) {
		if (quest_npcs.find(name) != quest_npcs.end()) {
			return *quest_npcs.find(name)->second;
		}
		else {
			auto animation_texture = multimedia_manager.get_texture(asset, 0, 0, 48, 48, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
			animation_texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });

			std::string font = assets::fonts::DEFAULT_FONT;
			auto name_texture = multimedia_manager.get_text(font, name, 14, { 255,0,0 });
			name_texture->set_position({ 0, -20 });
			name_texture->set_parent(animation_texture.get());

			auto interaction_texture = multimedia_manager.get_text(" ", 14);
			interaction_texture->set_position({ 0, -800 });
			interaction_texture->set_parent(animation_texture.get());


			auto& builder = entity_manager.create_entity("npc")
				.with_component<BaseComponent>(std::move(animation_texture), x, y, 48.0f, 48.0f)
				.with_component<QuestAIComponent>(name, std::move(name_texture))
				.with_component<InteractionComponent>(std::move(interaction_texture));
			auto base_component = builder.get().get<BaseComponent>();
			builder.with_component<ColliderComponent>(BoundaryRectangle(base_component->location.x, base_component->location.y, base_component->w, base_component->h));

			auto& quest_npc = builder.get();

			quest_npcs.insert(std::pair<std::string, const memecity::engine::ecs::Entity*>(name, &quest_npc));

			return quest_npc;
		}
	}
}

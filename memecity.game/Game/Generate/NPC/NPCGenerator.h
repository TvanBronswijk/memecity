#ifndef _NPCFACTORY_H
#define  _NPCFACTORY_H
#include <ECS.h>
#include <vector>
#include <map>
#include <Engine\MultimediaManager.h>
#include "..\..\..\Assets.h"
#include "..\..\Enum\AIStates.h"

namespace generate {
	class NPCGenerator {
	private:
		std::map<std::string,const memecity::engine::ecs::Entity*> quest_npcs;
		std::vector<std::string> names_boys;
		std::vector<std::string> names_girls;

		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::ecs::EntityManager& entity_manager;

		float x, y;
		int level = 0, strength = 0, perception = 0, endurance = 0, charisma = 0, intelligence = 0, agility = 0, luck = 0, health = 0, exp = 0, range_of_fighting = 0, movement_speed = 0;
		std::string animation_string, name;
	public:
		NPCGenerator(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager) 
			: multimedia_manager(multimedia_manager), entity_manager(entity_manager) 
		{
			names_boys = {"Rick", "Martijn", "Tobi", "Yoeri","Thom","Simon", "Roy", "Henk", "Jan", "Luke", "Jos", "Luuk", "Ramon", "Jeen", "Jack", "Thijn"};
			names_girls = {"Sanne", "Denise", "Samantha", "Ria","Eline","Kim", "Danielle", "Eefje", "Karen", "Tamara", "Kate", "Tess", "Ellen", "Kelly", "Taira", "Emy"};
		};

		int random_int(int max);
		const memecity::engine::ecs::Entity& generate_random_npc(float x, float y);
		const memecity::engine::ecs::Entity& generate_police_npc(float x, float y);
			const memecity::engine::ecs::Entity& generate_civilian_npc(float x, float y);
		const memecity::engine::ecs::Entity& generate_quest_npc(std::string name, assets::Asset asset);
		const memecity::engine::ecs::Entity& generate_npc(
			float x, float y,float width, float height,int level, int exp, int range_of_fighting, float movement_speed, int strength, int perception, int endurance, int charisma, 
			int intelligence, int agility, int luck, int health, std::string name, State state,
			std::unique_ptr<memecity::engine::texture::Texture> animation_texture, 
			std::unique_ptr<memecity::engine::texture::TextTexture> health_texture,
			std::unique_ptr<memecity::engine::texture::TextTexture> interaction_texture,
			std::unique_ptr<memecity::engine::texture::TextTexture> name_texture);
		std::vector<std::string> createInteractionStrings();
		std::string getRandomName();
	};
}
#endif


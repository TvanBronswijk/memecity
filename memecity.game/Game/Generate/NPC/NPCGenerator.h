#ifndef _NPCFACTORY_H
#define  _NPCFACTORY_H
#include <ECS.h>
#include <vector>
#include <map>
#include <Engine\MultimediaManager.h>
#include "..\..\..\Assets.h"
#include "..\..\Enum\AIStates.h"

enum class Gender {Male,Female};

namespace generate {
	class NPCGenerator {
	private:
		std::map<std::string,const memecity::engine::ecs::Entity*> quest_npcs;
		std::vector<std::string> names_boys;
		std::vector<std::string> names_girls;

		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::ecs::EntityManager& entity_manager;

		int min_fighting_range, min_movement_speed, min_base_points;

		Gender gender;
	public:
		NPCGenerator(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager) 
			: multimedia_manager(multimedia_manager), entity_manager(entity_manager) , min_fighting_range(60), min_movement_speed(180), min_base_points(5)
		{
			names_boys = {"Rick", "Martijn", "Tobi", "Yoeri","Thom","Simon", "Roy", "Henk", "Jan", "Luke", "Jos", "Luuk", "Ramon", "Jeen", "Jack", "Thijn"};
			names_girls = {"Sanne", "Denise", "Samantha", "Ria","Eline","Kim", "Danielle", "Eefje", "Karen", "Tamara", "Kate", "Tess", "Ellen", "Kelly", "Taira", "Emy"};
		};

		int random_int(int max);
		const memecity::engine::ecs::Entity& generate_random_npc(float x, float y);
		const memecity::engine::ecs::Entity& generate_police_npc(float x, float y);
			const memecity::engine::ecs::Entity& generate_civilian_npc(float x, float y);
		const memecity::engine::ecs::Entity& generate_quest_npc(std::string name,int x, int y, assets::Asset asset);
		const memecity::engine::ecs::Entity& generate_npc(
			float x, float y,float width, float height,int exp, int range_of_fighting, float movement_speed, int blikcoins, int strength, int perception, int endurance, int charisma,
			int intelligence, int agility, int luck, std::string name, Ai_State state, std::vector<std::string>interaction, int level,
			assets::Asset animation_character);
		std::vector<std::string> create_interaction_strings();
		std::string get_random_name();
	};
}
#endif


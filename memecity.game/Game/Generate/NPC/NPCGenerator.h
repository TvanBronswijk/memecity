#ifndef _NPCFACTORY_H
#define  _NPCFACTORY_H
#include <ECS.h>
#include <vector>
#include <Engine\MultimediaManager.h>

namespace generate {
	class NPCGenerator {
	private:
		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::sdl::TimerFacade& timer;
		memecity::engine::ecs::EntityManager& entity_manager;

		float x, y;
		int level = 0, strength = 0, perception = 0, endurance = 0, charisma = 0, intelligence = 0, agility = 0, luck = 0, health = 0;
		std::string animation_string;
	public:
		NPCGenerator(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::sdl::TimerFacade& timer, memecity::engine::ecs::EntityManager& entity_manager) 
			: multimedia_manager(multimedia_manager), timer(timer), entity_manager(entity_manager) {};

		int random_int(int max);
		const memecity::engine::ecs::Entity& generate_random_npc(int level, float x, float y);
		const memecity::engine::ecs::Entity& generate_npc(
			int level, float x, float y, int strength, int perception, int endurance, int charisma, 
			int intelligence, int agility, int luck, int health, 
			std::unique_ptr<memecity::engine::texture::Texture> animation_texture, 
			std::unique_ptr<memecity::engine::texture::TextTexture> health_texture,
			std::unique_ptr<memecity::engine::texture::TextTexture> interaction_texture);
	};
}
#endif


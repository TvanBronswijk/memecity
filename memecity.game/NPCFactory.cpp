#include"NPCFactory.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

const memecity::engine::ecs::Entity& NPCFactory::getRandomNPC(int maxlevel) {
	this->level = rand() % maxlevel;
	this->x = rand() % multimedia_manager.get_screen_width();
	this->y = rand() % multimedia_manager.get_screen_height();

	int points = level * 5;
	int strength_points = (rand() % points);
	strength += strength_points;
	points -= strength_points;
	int perception_points = (rand() % points);
	perception += perception_points;
	points -= perception_points;
	int endurance_points = (rand() % points);
	endurance += endurance_points;
	points -= endurance_points;
	int charisma_points = (rand() % points);
	charisma += charisma_points;
	points -= charisma_points;
	int intelligence_points = (rand() % points);
	intelligence += intelligence_points;
	points -= intelligence_points;
	int agility_points = (rand() % points);
	agility += agility_points;
	points -= agility_points;
	luck += points;

	health = ((strength * 5) + (endurance * 3) + (agility * 2) + 50);

	std::string hp = "HP: ";
	hp += std::to_string(health);
	hp += "/";
	hp += std::to_string(health);

	auto animation_texture = multimedia_manager.get_animated_texture(timer, animation_string, 0, 0, 48, 48, 4, 0.5f, texture::AnimatedTexture::AnimationDirection::vertical);//did not move bcause of the *timer
	animation_texture->set_position({ x , y + (multimedia_manager.get_screen_height() - (y * 2)) });//TODO: change when position can be placed correctly

	auto health_texture = multimedia_manager.get_text_texture(hp, "Minecraftia-Regular.ttf", 10, { 34,139,34 });
	health_texture->set_position({ 0, -20 });
	//health_texture->set_parent(animation_texture.get());

	auto interaction_texture = multimedia_manager.get_text_texture(" ", "Minecraftia-Regular.ttf", 14, { 255,255,255 });
	interaction_texture->set_position({ 0, -35 });
	//interaction_texture->set_parent(animation_texture.get());

	auto& npc = builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<AIComponent>()
		.with_component<VelocityComponent>()
		.with_component<PositionComponent>(x, y)
		.with_component<LevelComponent>(level)
		.with_component<StatsComponent>(strength,perception,endurance,charisma,intelligence,agility,luck)
		//.with_component<DrawableComponent>(std::move(animation_texture))//body of npc
		//.with_component<HealthComponent>(std::move(health_texture))
		//.with_component<InteractionComponent>(std::move(interaction_texture))
		.get();

	return npc;
}

//const memecity::engine::ecs::Entity& NPCFactory::getNPC(int level) {
//
//}


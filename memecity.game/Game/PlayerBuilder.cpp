#include "PlayerBuilder.h"
#include "Components.h"
#include "../Assets.h"
#include "Builder/QuestBuilder.h"
#include "Components/ScoreComponent.h"

int rand_stat() {
	return 1 + (rand() % 3);
}

const memecity::engine::ecs::Entity& PlayerBuilder::build(memecity::engine::ecs::EntityManager & em, memecity::engine::ui::loading::LoadingBar::Listener & listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();
	listener.set_text("Generating Player...");
	listener.set_max_value(100.0f);

	auto texture = multimedia_manager.get_texture(assets::spritesheets::HUMAN_MALE_1, 0, 0, 48, 48, 4, 0.25f, memecity::engine::texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });

	auto builder = em.create_entity("player")
		.with_component<BaseComponent>(std::move(texture), _start.x, _start.y, 48.0f, 48.0f)
		.with_component<PlayerComponent>(QuestBuilder(multimedia_manager, em).get_all_stories())
		.with_component<StatsComponent>(rand_stat(), rand_stat(), rand_stat(), rand_stat(), rand_stat(), rand_stat(), rand_stat())
		.with_component<AnimationComponent>()
		.with_component<ExpComponent>(0, 100)
		.with_component<HealthComponent>(100, nullptr)
		.with_component<InventoryComponent>()
		.with_component<ScoreComponent>()
		.with_component<VelocityComponent>();
	
	auto base_component = builder.get().get<BaseComponent>();
	builder.with_component<ColliderComponent>(BoundaryRectangle(base_component->location.x, base_component->location.y, base_component->w, base_component->h));
	
	listener.increase_current_value(100.0f);
	return builder.get();
}

#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\..\GameManager.h"

struct MoveEventArgs;

class AnimationSystem : public memecity::engine::ecs::System
{
private:
	GameManager::GameContext* _context;

public:
	AnimationSystem(GameManager::GameContext& context) : _context(&context) {}
	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_move(memecity::engine::ecs::EntityManager & em, MoveEventArgs ea);

	void set_texture(BaseComponent& base_component, std::unique_ptr<memecity::engine::texture::Texture> texture) const;
};

#endif

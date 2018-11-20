#ifndef _DRAWABLECOMPONENT_H
#define _DRAWABLECOMPONENT_H
#include <Engine\Textures.h>
#include <ECS.h>

struct DrawableComponent : public memecity::engine::ecs::Component
{
private:
	std::unique_ptr<memecity::engine::texture::Texture> texture;

public:
	DrawableComponent(const memecity::engine::ecs::Entity& entity)
		: DrawableComponent(entity, nullptr) {}
	DrawableComponent(const memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture)
		: memecity::engine::ecs::Component(entity), texture(std::move(texture)){}
	/*DrawableComponent(const memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture, memecity::engine::texture::Texture& parent)
		: memecity::engine::ecs::Component(entity), texture(std::move(texture)) {
		get_texture().set_parent(&parent);
	}*/

	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}
};

#endif


#ifndef _BASE_COMPONENT_H
#define  _BASE_COMPONENT_H
#include <Engine\Textures.h>
#include "..\Component.h"
struct BaseComponent : public memecity::engine::ecs::Component
{
protected:
	std::unique_ptr<memecity::engine::texture::Texture> _texture;
public:
	uPoint<float> location;
	float w, h;
	BaseComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture, Rectangle rect)
		: BaseComponent(entity, std::move(texture), rect.x, rect.y, rect.w, rect.h) {}
	BaseComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture, float x, float y, float w, float h)
		: Component(entity), _texture(std::move(texture)), location({ x, y }), w(w), h(h) {}
	void set_texture(std::unique_ptr<memecity::engine::texture::Texture> texture) { _texture = std::move(texture); }
	memecity::engine::texture::Texture& get_texture(){ return *_texture; }
};
#endif

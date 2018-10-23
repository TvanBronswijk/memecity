#include "ColliderComponent.h"

std::string ColliderComponent::COMPONENT_TYPE = "ColliderComponent";

ColliderComponent::ColliderComponent(Entity* e) : Component(e)
{
}

ColliderComponent::ColliderComponent(Entity * e, Texture *texture) : Component(e)
{
	this->texture = texture;
}

std::string ColliderComponent::get_type()
{
	return COMPONENT_TYPE;
}

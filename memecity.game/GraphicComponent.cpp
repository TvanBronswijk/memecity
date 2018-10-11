#include "GraphicComponent.h"

GraphicComponent::GraphicComponent(Texture* texture)
{
	this->texture = texture;
}

std::string GraphicComponent::get_type()
{
	return "GraphicComponent";
}

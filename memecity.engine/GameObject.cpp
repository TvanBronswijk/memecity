#include "GameObject.h"

GameObject::GameObject(const float x, const float y)
{
	position.x = x;
	position.y = y;

	rotation = 0.0f;
	is_active = true;
	parent = nullptr;
}

GameObject::~GameObject()
{
	parent = nullptr;
}

void GameObject::set_position(const Vector2 position)
{
	this->position = position;
}

Vector2 GameObject::get_position(const SPACE space)
{
	if (space == local || parent == nullptr)
		return position;

	return parent->get_position(world) + RotateVector(position, parent->get_rotation(local));
}
void GameObject::set_rotation(float rotation) const
{
	rotation = rotation;
	if (rotation > 360.0f) {
		const int mul = rotation / 360;
		rotation -= 360.0f * mul;
	}
	else if (rotation < 0.0f) {
		const int mul = (rotation / 360) - 1;
		rotation -= 360.0f * mul;
	}
}

float GameObject::get_rotation(const SPACE space) const
{
	if (space == local || parent == nullptr)
		return rotation;

	return parent->get_rotation(world) + rotation;
}

void GameObject::set_active(const bool active)
{
	is_active = active;
}

bool GameObject::get_active() const
{
	return is_active;
}

void GameObject::get_parent(std::shared_ptr<GameObject> parent)
{
	position = get_position(world) - parent->get_position(world);
	parent = parent;
}

std::shared_ptr<GameObject> GameObject::get_parent() const
{
	return parent;
}

void GameObject::translate(const Vector2 vector)
{
	position += vector;
}


void GameObject::update()
{

}

void GameObject::render()
{

}

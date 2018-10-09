#include "GameObject.h"

/**
 * Create a new GameObject on given x and y values (position)
 */
GameObject::GameObject(float x, float y)
{
	position.x = x;
	position.y = y;

	rotation = 0.0f;
	is_active = true;
	parent = nullptr;
}

/**
 * Sets the parent of the GameObject to a nullptr to avoid memory leaks
 */
GameObject::~GameObject()
{
	parent = nullptr;
}

/**
 * Sets the position
 */
void GameObject::set_position(Vector2 position)
{
	this->position = position;
}

/**
 * Returns position based on given SPACE
 */
Vector2 GameObject::get_position(SPACE space)
{
	if (space == local || parent == nullptr)
	{
		return position;
	}

	return parent->get_position(world) + RotateVector(position, parent->get_rotation(local));
}

/**
 * Sets the rotation
 */
void GameObject::set_rotation(float rotation)
{
	this->rotation = rotation;
	if (rotation > 360.0f) 
	{
		const int mul = rotation / 360;
		this->rotation -= 360.0f * mul;
	}
	else if (rotation < 0.0f) 
	{
		const int mul = (rotation / 360) - 1;
		this->rotation -= 360.0f * mul;
	}
}

/**
 * Gets the rotation based on given SPACE
 */
float GameObject::get_rotation(SPACE space) const
{
	if (space == local || parent == nullptr)
	{
		return rotation;
	}

	return parent->get_rotation(world) + rotation;
}

/*
 * Sets if the GameObject is active
 */
void GameObject::set_active(bool active)
{
	is_active = active;
}

/**
 * Returns whether the GameObject is active
 */
bool GameObject::get_active() const
{
	return is_active;
}

/**
 * Sets the parent
 */
void GameObject::set_parent(std::shared_ptr<GameObject> parent)
{
	position = get_position(world) - parent->get_position(world);
	this->parent = parent;
}

/**
 * Returns the parent
 */
std::shared_ptr<GameObject> GameObject::get_parent() const
{
	return parent;
}

/**
 * Update position based on given vector
 */
void GameObject::translate(Vector2 vector)
{
	position += vector;
}

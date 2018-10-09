#include "GameObject.h"

///<summary>Create a new GameObject on given x and y values (position).</summary>
GameObject::GameObject(float x, float y)
{
	position.x = x;
	position.y = y;

	rotation = 0.0f;
	is_active = true;
	parent = nullptr;
}

///<summary>Sets the parent of the GameObject to a nullptr to avoid memory leaks.</summary>
GameObject::~GameObject()
{
	parent = nullptr;
}

///<summary>Sets the position.</summary>
void GameObject::set_position(Vector2 position)
{
	this->position = position;
}

///<summary>Returns position based on given SPACE.</summary>
Vector2 GameObject::get_position(SPACE space)
{
	if (space == local || parent == nullptr)
	{
		return position;
	}

	return parent->get_position(world) + RotateVector(position, parent->get_rotation(local));
}

///<summary>Sets the rotation.</summary>
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

///<summary>Gets the rotation based on given SPACE.</summary>
float GameObject::get_rotation(SPACE space) const
{
	if (space == local || parent == nullptr)
	{
		return rotation;
	}

	return parent->get_rotation(world) + rotation;
}

///<summary>Sets if the GameObject is active.</summary>
void GameObject::set_active(bool active)
{
	is_active = active;
}

///<summary>Returns whether the GameObject is active.</summary>
bool GameObject::get_active() const
{
	return is_active;
}

///<summary>Sets the parent.</summary>
void GameObject::set_parent(std::shared_ptr<GameObject> parent)
{
	position = get_position(world) - parent->get_position(world);
	this->parent = parent;
}

///<summary>Returns the parent.</summary>
std::shared_ptr<GameObject> GameObject::get_parent() const
{
	return parent;
}

///<summary>Update position based on given vector.</summary>
void GameObject::translate(Vector2 vector)
{
	position += vector;
}

#include "GameObject.h"

namespace memecity::engine::texture {
	GameObject::GameObject(float x, float y)
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

	void GameObject::set_position(Vector2 position)
	{
		this->position = position;
	}

	Vector2 GameObject::get_position(SPACE space)
	{

		if (space == local || parent == nullptr)
		{
			return position;
		}
		return parent->get_position(world) + RotateVector(position, parent->get_rotation(local));
	}

	void GameObject::set_rotation(float rotation)
	{
		this->rotation = rotation;
		if (rotation > 360.0f)
		{
			const float mul = rotation / 360;
			this->rotation -= 360.0f * mul;
		}
		else if (rotation < 0.0f)
		{
			const float mul = (rotation / 360) - 1;
			this->rotation -= 360.0f * mul;
		}
	}

	float GameObject::get_rotation(SPACE space) const
	{
		if (space == local || parent == nullptr)
		{
			return rotation;
		}

		return parent->get_rotation(world) + rotation;
	}

	void GameObject::set_active(bool active)
	{
		is_active = active;
	}

	bool GameObject::get_active() const
	{
		return is_active;
	}

	void GameObject::set_parent(GameObject* parent)
	{
		this->parent = parent;
	}

	GameObject* GameObject::get_parent() const
	{
		return parent;
	}

	void GameObject::translate(Vector2 vector)
	{
		if (parent == nullptr)
			position += vector;
	}
}

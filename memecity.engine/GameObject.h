#ifndef _GRAPHIC_H
#define  _GRAPHIC_H

#include "MathHelper.h"
#include "GraphicsFacade.h"

class GameObject
{
public:
	enum SPACE { local = 0, world = 1 };

private:
	Vector2 position;
	float rotation;

	bool is_active;
	std::unique_ptr<GameObject>::pointer parent;

public:
	///<summary>Create a new GameObject on given x and y values (position).</summary>
	GameObject(float x = 0.0f, float y = 0.0f);

	///<summary>Sets the parent of the GameObject to a nullptr to avoid memory leaks.</summary>
	virtual ~GameObject();

	///<summary>Sets the position.</summary>
	void set_position(Vector2 position);

	///<summary>Returns position based on given SPACE.</summary>
	Vector2 get_position(SPACE space = world);

	///<summary>Sets the rotation.</summary>
	void set_rotation(float rotation);

	///<summary>Gets the rotation based on given SPACE.</summary>
	float get_rotation(SPACE space = world) const;

	///<summary>Sets if the GameObject is active.</summary>
	void set_active(bool active);

	///<summary>Returns whether the GameObject is active.</summary>
	bool get_active() const;

	///<summary>Sets the parent.</summary>
	void set_parent(std::unique_ptr<GameObject>::pointer parent);
	
	///<summary>Returns the parent.</summary>
	std::unique_ptr<GameObject>::pointer get_parent() const;

	///<summary>Update position based on given vector.</summary>
	void translate(Vector2 vector);

};

#endif
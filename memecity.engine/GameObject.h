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
	std::shared_ptr<GameObject> parent;

public:
	GameObject(float x = 0.0f, float y = 0.0f);
	virtual ~GameObject();

	void set_position(Vector2 position);
	Vector2 get_position(SPACE space = world);

	void set_rotation(float rotation);
	float get_rotation(SPACE space = world) const;

	void set_active(bool active);
	bool get_active() const;

	void set_parent(std::shared_ptr<GameObject> parent);
	std::shared_ptr<GameObject> get_parent() const;

	void translate(Vector2 vector);

	virtual void render() = 0;
};

#endif
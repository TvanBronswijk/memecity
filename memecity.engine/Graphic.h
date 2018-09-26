#ifndef _GRAPHIC_H
#define  _GRAPHIC_H
#include "MathHelper.h"

class Graphic
{
public:
	enum SPACE { local = 0, world = 1 };

private:
	Vector2 mPos;
	float mRotation;

	bool mActive;
	Graphic* mParent;

public:
	Graphic(float x = 0.0f, float y = 0.0f);
	~Graphic();

	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = world);

	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	void Active(bool active);
	bool Active();

	void Parent(Graphic* parent);
	Graphic* Parent();

	void Translate(Vector2 vec);

	virtual void Update();
	virtual void Render();
};

#endif
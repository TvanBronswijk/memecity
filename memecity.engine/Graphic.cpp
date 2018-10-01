#include "Graphic.h"

Graphic::Graphic(float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	mRotation = 0.0f;
	mActive = true;
	mParent = nullptr;
}

Graphic::~Graphic()
{
	mParent = nullptr;
}

void Graphic::Pos(Vector2 pos)
{
	mPos = pos;
}

Vector2 Graphic::Pos(SPACE space)
{
	if (space == local || mParent == nullptr)
		return mPos;

	return mParent->Pos(world) + RotateVector(mPos, mParent->Rotation(local));
}
void Graphic::Rotation(float rotation)
{
	mRotation = rotation;

	if (mRotation > 360.0f) {
		int mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if (mRotation < 0.0f) {
		int mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float Graphic::Rotation(SPACE space)
{
	if (space == local || mParent == nullptr)
		return mRotation;

	return mParent->Rotation(world) + mRotation;
}

void Graphic::Active(bool active)
{
	mActive = active;
}

bool Graphic::Active()
{
	return mActive;
}

void Graphic::Parent(Graphic* parent)
{
	mPos = Pos(world) - parent->Pos(world);

	mParent = parent;
}

Graphic* Graphic::Parent()
{
	return mParent;
}

void Graphic::Translate(Vector2 vec)
{
	mPos += vec;
}


void Graphic::Update()
{

}

void Graphic::Render()
{

}

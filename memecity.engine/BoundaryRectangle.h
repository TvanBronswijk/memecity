#ifndef _BOUNDARY_RECTANGLE_H
#define _BOUNDARY_RECTANGLE_H

#include "Engine/Util/Rectangle.h"

struct BoundaryRectangle
{
	float &x, &y, &w, &h;

	BoundaryRectangle(float& x, float& y, float& w, float& h) : x(x), y(y), w(w), h(h) {}

	~BoundaryRectangle() = default;
};

#endif
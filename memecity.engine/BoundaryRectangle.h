#ifndef _BOUNDARY_RECTANGLE_H
#define _BOUNDARY_RECTANGLE_H

#include "Engine/Util/Rectangle.h"

class BoundaryRectangle : public Rectangle
{
public:
	BoundaryRectangle(float x, float y, float w, float h) : Rectangle(x, y, w, h) {};
	bool contains(const BoundaryRectangle &other) const
	{
		return this->contains(other.x, other.y);
	}

	bool contains(const int other_x, const int other_y) const
	{
		return (other_x >= x - w &&
			other_x <= x + w &&
			other_y >= y - h &&
			other_y <= y + h);
	}

	bool intersects(const BoundaryRectangle &other) const
	{
		return !(other.x - other.w > x + w ||
			other.x + other.w < x - w ||
			other.y - other.h > y + h ||
			other.y + other.h < x - h);
	}
};

#endif
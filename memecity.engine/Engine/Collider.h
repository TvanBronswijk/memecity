#ifndef _COLLIDER_H
#define _COLLIDER_H

struct Collider
{
	int x, y, w, h;

	Collider(const int x, const int y, const int w, const int h) : x(x), y(y), w(w), h(h) {}
	Collider() = default;

	bool contains(const Collider &other) const
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

	bool intersects(const Collider &other) const
	{
		return !(other.x - other.w > x + w ||
			other.x + other.w < x - w ||
			other.y - other.h > y + h ||
			other.y + other.h < x - h);
	}
};

#endif
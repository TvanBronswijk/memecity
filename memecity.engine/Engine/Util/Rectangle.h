#ifndef _RECTANGLE_H
#define _RECTANGLE_H
struct Rectangle
{
	int x, y, w, h;
	Rectangle(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) {};
	Rectangle() = default;
	virtual ~Rectangle() = default;

	bool contains(const Rectangle &other) const
	{
		return this->contains(other.x, other.y);
	}

	bool contains(int other_x, int other_y) const
	{
		return (other_x >= x - w &&
			other_x <= x + w &&
			other_y >= y - h &&
			other_y <= y + h);
	}

	bool intersects(Rectangle &other) const
	{
		return !(other.x - other.w > x + w ||
			other.x + other.w < x - w ||
			other.y - other.h > y + h ||
			other.y + other.h < x - h);
	}
};

#endif


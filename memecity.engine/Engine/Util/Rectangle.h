#ifndef _RECTANGLE_H
#define _RECTANGLE_H

struct Rectangle
{
	float x, y, w, h;
	Rectangle(float x, float y, float w, float h)
		: x(x), y(y), w(w), h(h) {};
	Rectangle() = default;
	virtual ~Rectangle() = default;
};

template<class Rect1, class Rect2>
bool intersects(const Rect1& l, const Rect2& r)
{
	return (l.x < r.x + r.w &&
		l.y < r.y + r.h &&
		r.x < l.x + l.w &&
		r.y < l.y + l.h);
}

template<class Rect1, class Rect2>
bool contains(const Rect1& l, const Rect2& r)
{
	return (r.x >= l.x - l.w &&
		r.x <= l.x + l.w &&
		r.y >= l.y - l.h &&
		r.y <= l.y + l.h);
}
#endif


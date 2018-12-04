#ifndef _RECTANGLE_H
#define _RECTANGLE_H

template<class T>
struct uPoint {
	T x, y;
	uPoint() 
		: uPoint(0, 0) {}
	uPoint(T x, T y)
		: x(x), y(y) {}
	virtual ~uPoint() = default;
};
using Point = uPoint<float>;

template<class T>
struct uRectangle {
	T x, y, w, h;
	const uPoint<T> begin, end, center;
	uRectangle()
		: uRectangle(0, 0, 0, 0) {}
	uRectangle(T x, T y, T w, T h)
		: x(x), y(y), w(w), h(h), begin(x, y), end((x + w - 1), (y + h - 1)), center({ x + (w / 2), y + (h / 2) }) {}
	virtual ~uRectangle() = default;
};
using Rectangle = uRectangle<float>;

template<class Rect1, class Rect2>
bool intersects(const Rect1& l, const Rect2& r)
{
	return (l.x < r.x + r.w
		&& l.x + l.w > r.x
		&& l.y < r.y + r.h
		&& l.y + l.h > r.y);
}
#endif


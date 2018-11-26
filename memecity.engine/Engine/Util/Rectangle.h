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

#endif


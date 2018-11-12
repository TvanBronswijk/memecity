#ifndef _RECTANGLE_H
#define _RECTANGLE_H
struct Rectangle
{
	int x, y, w, h;
	Rectangle(int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h) {};
	Rectangle() = default;
	virtual ~Rectangle() = default;
};

#endif


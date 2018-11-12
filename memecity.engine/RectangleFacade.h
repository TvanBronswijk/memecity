#ifndef _RECTANGLEFACADE_H
#define _RECTANGLEFACADE_H
struct RectangleFacade
{
	int x, y, w, h;
	RectangleFacade(int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h) {};
	RectangleFacade() = default;
	virtual ~RectangleFacade() = default;
};

#endif


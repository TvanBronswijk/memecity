#ifndef _COLLIDER_H
#define _COLLIDER_H

struct Collider
{
	int &x, &y, &w, &h;

	Collider(int &x, int &y, int &w, int &h) : x(x), y(y), w(w), h(h) {}
};

#endif
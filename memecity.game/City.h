#ifndef _CITY_MODELS_H
#define _CITY_MODELS_H
#include <vector>
#include <iostream>

struct Rectangle {
	int x;
	int y;
	int w;
	int h;

	int x2;
	int y2;
	int center_x;
	int center_y;

	Rectangle(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->x2 = x + w - 1;
		this->y2 = y + h - 1;
		this->center_x = (x + x2) / 2;
		this->center_y = (y + y2) / 2;
	}
};

struct Base64_Tilemap : Rectangle {
	char* tiles;
	Base64_Tilemap(int w, int h) : Rectangle (0, 0, w, h)
	{
		this->tiles = new char[w*h];
	}

	virtual char& coord(int x, int y)
	{
		return tiles[x * h + y];
	}
};

struct City : Base64_Tilemap {
	City(int w, int h) : Base64_Tilemap(w, h)
	{
	}
};

struct Prefab : Base64_Tilemap {
	Prefab(int w, int h, char* tiles) : Base64_Tilemap(w, h)
	{
		this->tiles = tiles;
	}
};

#endif
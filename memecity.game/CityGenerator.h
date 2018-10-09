#ifndef _CITY_GENERATOR_H
#define _CITY_GENERATOR_H
#include <vector>
#include <iostream>

struct Node {
	int x;
	int y; 
	int w;
	int h;

	Node* left;
	Node* right;
};

class City {
private:
	std::vector<int> tiles;
public:
	int w;
	int h;

	City(int w, int h) 
	{
		this->w = w;
		this->h = h;

		for (int i = 0; i < (w*h); i++)
			tiles.at(i) = 0;
	}

	int& coord(int x, int y) 
	{
		return tiles.at(x * h + y);
	}
};

class CityGenerator {
private:
	const static int MIN_NODE_WIDTH = 32;
	const static int MIN_NODE_HEIGHT = 32;
public:
	std::unique_ptr<City> generate(int w, int h);
};

#endif
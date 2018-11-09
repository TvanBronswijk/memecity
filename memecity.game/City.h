#ifndef _CITY_MODELS_H
#define _CITY_MODELS_H
#include <vector>
#include <iostream>

namespace generate {
	namespace models {
		struct Rectangle {
			int x, y, w, h;
			int x2, y2, center_x, center_y;
			Rectangle(int x, int y, int w, int h)
				: x(x), y(y), w(w), h(h), x2(x + w - 1), y2(y + h - 1), center_x((x + x2) / 2), center_y((y + y2) / 2) {}
		};

		struct Base64_Tilemap : Rectangle {
			char* tiles;
			Base64_Tilemap(int w, int h) : Rectangle(0, 0, w, h)
			{
				this->tiles = new char[w*h];
			}

			virtual char& coord(int x, int y)
			{
				return tiles[x * h + y];
			}

			virtual const char& coord(int x, int y) const
			{
				return tiles[x * h + y];
			}

			virtual ~Base64_Tilemap()
			{
				delete tiles;
			}
		};

		struct City : Base64_Tilemap {
			City(int w, int h) : Base64_Tilemap(w, h) {}
		};

		struct Prefab : Base64_Tilemap {
			Prefab(int w, int h, char* tiles) : Base64_Tilemap(w, h) { this->tiles = tiles; }
		};
	}
}


#endif

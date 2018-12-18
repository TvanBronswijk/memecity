#ifndef _CITY_MODELS_H
#define _CITY_MODELS_H
#include <map>
#include <Engine\Util.h>
#include "..\..\..\..\Assets.h"

namespace generate::models {
	struct Base64_Tilemap : uRectangle<int> {
	protected:
		char* tiles;
	public:
		Base64_Tilemap(int w, int h)
			: uRectangle(0, 0, w, h), tiles(new char[w*h]) { }
		Base64_Tilemap(const Base64_Tilemap& copy) : Base64_Tilemap(copy.w, copy.h) {
			for (int i = 0; i < w*h; i++) {
				tiles[i] = (copy.tiles[i]);
			}
		}
		virtual char& coord(int x, int y) { return tiles[x * h + y]; }
		virtual const char& coord(int x, int y) const { return tiles[x * h + y]; }
		virtual char& operator () (int x, int y) { return coord(x, y); }
		virtual const char& operator () (int x, int y) const { return coord(x, y); }
		virtual char* operator [] (int x) { return &tiles[x * h]; }
		virtual const char* operator [] (int x) const { return &tiles[x * h]; }
		virtual ~Base64_Tilemap() override { delete tiles; }
	};

	struct City {
		int width, height;
		uPoint<int> start;
		Base64_Tilemap tiles;
		Base64_Tilemap objects;
		City(int w, int h) 
			: width(w), height(h), tiles(w, h), objects(w, h) {}
	};

	struct Prefab {
		int width, height;
		Base64_Tilemap tiles;
		Base64_Tilemap objects;
		Prefab(int w, int h, const char* tiles, const char* objects)
			: width(w), height(h), tiles(w, h), objects(w, h) {
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					this->tiles(x, y) = tiles[x * h + y];
					this->objects(x, y) = objects[x * h + y];
				}
			}
		}
	};

	static const std::map<char, std::map<assets::Asset, int>> __cta {
		{'-', assets::sprites::tiles::ROAD },
		{'w', assets::sprites::tiles::WATER },
		{'g', assets::sprites::tiles::GRASS },
		{'W', assets::sprites::tiles::WALL }
	};
	static assets::Asset char_to_asset(char c) {
		const auto index = rand() % 100;

		for (auto item : __cta.at(c))
		{
			if (index < item.second)
			{
				return item.first;
			}
		}
		return __cta.at(c).begin()->first;
	}
}


#endif

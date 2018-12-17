#ifndef _CITY_MODELS_H
#define _CITY_MODELS_H
#include <map>
#include <Engine\Util.h>
#include "..\..\..\..\Assets.h"

namespace generate::models {
	struct Base64_Tilemap : uRectangle<int> {
	protected:
		std::string tiles;
	public:
		Base64_Tilemap(int w, int h)
			: uRectangle(0, 0, w, h), tiles(new char[w*h]) { }
		Base64_Tilemap(const Base64_Tilemap& copy) : Base64_Tilemap(copy.w, copy.h) {
			tiles = copy.tiles;
		}
		virtual char& coord(int x, int y) { return tiles[x * h + y]; }
		virtual const char& coord(int x, int y) const { return tiles[x * h + y]; }
		virtual char& operator () (int x, int y) { return coord(x, y); }
		virtual const char& operator () (int x, int y) const { return coord(x, y); }
		virtual ~Base64_Tilemap() = default;
		virtual std::string get_tile_string() const
		{
			std::string s;
			for (int i = 0; i < w*h; i++) {
				s += tiles[i];
				if ((i+1) % w == 0)
				{
					s += "\n";
				}
			}
			return s;
		}
	};

	struct City : Base64_Tilemap {
		City(int w, int h)
			: Base64_Tilemap(w, h) {}
	};

	struct Prefab : Base64_Tilemap {
		Prefab(int w, int h, const char* tiles)
			: Base64_Tilemap(w, h) {
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					this->coord(x, y) = tiles[x * h + y];
				}
			}
		}
	};

	static const std::map<char, assets::Asset> __cta {
		{'-', assets::sprites::tiles::ROAD },
		{'w', assets::sprites::tiles::WATER },
		{'g', assets::sprites::tiles::GRASS },
		{'W', assets::sprites::tiles::WALL }
	};
	static assets::Asset char_to_asset(char c) {
		return __cta.at(c);
	}
}


#endif

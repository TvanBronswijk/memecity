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
		virtual std::string get_tile_string() const
		{
			std::string s;
			for (int i = 0; i < w*h; i++) {
				s += tiles[i];
				if ((i + 1) % w == 0)
				{
					s += "\n";
				}
			}
			return s;
		}
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

	static const Prefab station(8, 8, 
		"--------"
		"-WWWWWW-"
		"-WmmmmW-"
		"-WmccmW-"
		"-WmccmW-"
		"-WmmmmW-"
		"-WWmmWW-"
		"--------",
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0");

	struct TileInfo {
		char character;
		const char *name;
		assets::AssetMap asset;
		bool blocked, block_sight;
		TileInfo(char character, const char* name, assets::AssetMap asset, bool blocked, bool block_sight) 
			: character(character), name(name), asset(asset), blocked(blocked), block_sight(block_sight) {}
		assets::Asset get_asset() {
			const auto index = rand() % 100;
			for (auto& pair : asset) {
				if (index < pair.second) {
					return pair.first;
				}
			}
			return asset.begin()->first;
		}
	};

	static const std::map<char, TileInfo> __cta {
		{'-', {'-', "Road", assets::sprites::tiles::ROAD, false, false } },
		{'w', {'w', "Water", assets::sprites::tiles::WATER, true, false } },
		{'g', {'g', "Grass", assets::sprites::tiles::GRASS, false, false } },
		{'W', {'W', "Wall", assets::sprites::tiles::WALL, true, true } },
		{'m', {'m', "Marble White", assets::sprites::tiles::MARBLEWHITE, false, false } },
		{'B', {'B', "Marble Black", assets::sprites::tiles::MARBLEBLACK, false, false } },
		{'f', {'f', "Hardwood", assets::sprites::tiles::HARDWOOD, false, false } },
		{'d', {'d', "Hardwood Dark", assets::sprites::tiles::HARDWOODDARK, false, false } },
		{'b', {'b', "Carpet Brown", assets::sprites::tiles::CARPETBROWN, false, false } },
		{'l', {'l', "Carpet Light Gray", assets::sprites::tiles::CARPETLIGHTGRAY, false, false } },
		{'t', {'t', "Carpet Tan", assets::sprites::tiles::CARPETTAN, false, false } },
		{'c', {'c', "Station", assets::sprites::tiles::STATION, false, false } }
	};
	static TileInfo char_to_tile(char c) {
		auto it = __cta.find(c);
		if (it != __cta.end()) {
			return it->second;
		}
		return TileInfo{ c, "Not Found", {}, false, false };
	}
}


#endif

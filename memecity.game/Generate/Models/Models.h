#ifndef _CITY_MODELS_H
#define _CITY_MODELS_H
#include <vector>
#include <map>

namespace generate::models {
	struct Point {
		int x, y;
		Point(int x, int y) 
			: x(x), y(y) {}
		~Point() = default;
	};

	struct Rectangle {
		int x, y, w, h;
		const Point begin, end, center;
		Rectangle(int x, int y, int w, int h)
			: x(x), y(y), w(w), h(h), begin(x, y), end((x + w - 1), (y + h - 1)), center({x + (w/2), y + (h/2)}) {}
		virtual ~Rectangle() = default;
	};

	struct Base64_Tilemap : Rectangle {
	protected:
		char* tiles;
	public:
		Base64_Tilemap(int w, int h)
			: Rectangle(0, 0, w, h), tiles(new char[w*h]) { }
		Base64_Tilemap(const Base64_Tilemap& copy) : Base64_Tilemap(copy.w, copy.h) {
			for (int i = 0; i < w*h; i++) {
				tiles[i] = (copy.tiles[i]);
			}
		}
		virtual char& coord(int x, int y) { return tiles[x * h + y]; }
		virtual const char& coord(int x, int y) const { return tiles[x * h + y]; }
		virtual char& operator () (int x, int y) { return coord(x, y); }
		virtual const char& operator () (int x, int y) const { return coord(x, y); }
		virtual ~Base64_Tilemap() override { delete tiles; }
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
		Prefab(int w, int h, const char** tiles) :
			Base64_Tilemap(w, h) {
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					this->coord(x, y) = tiles[x][y];
				}
			}
		}
	};

	struct TileInfo {
		const char *name, base64_character, *filename;
		TileInfo(const char* name, const char base64_character, const char* filename)
			: name(name), base64_character(base64_character), filename(filename) {};
		~TileInfo() = default;
	};

	namespace Tiles {
		static const TileInfo ROAD = { "Road", '-', "gray.bmp" };
		static const TileInfo WALL = { "Wall", 'W', "brown.bmp" };
		static const TileInfo WATER = { "Water", 'w', "blue.bmp" };
		static const TileInfo GRASS = { "Grass", 'g', "green.bmp" };
	}
}


#endif

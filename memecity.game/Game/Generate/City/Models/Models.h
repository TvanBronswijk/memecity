#ifndef _CITY_MODELS_H
#define _CITY_MODELS_H
#include <Engine\Util.h>

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
}


#endif

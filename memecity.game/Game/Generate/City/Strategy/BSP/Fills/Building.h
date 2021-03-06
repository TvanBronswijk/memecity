#ifndef _GENERATE_BUILDING_H
#define _GENERATE_BUILDING_H
#include "Fill.h"

namespace generate::strategy::bsp {
	class Building : public Fill {
	private:
		int _road_size;
	public:
		Building() : Building(1) {};
		Building(int road_size) : _road_size(road_size) {}
		~Building() = default;
		void write(models::City& c, const Node& n) const override {
			iterate(n, [&](int x, int y) {
				c.tiles(x, y) = '-';

				if (x > n.begin.x + _road_size && x < n.end.x - _road_size
					&& y > n.begin.y + _road_size && y < n.end.y - _road_size) {
					c.tiles(x, y) = 'l';
				}

				if (x >= (n.begin.x + _road_size) && x <= (n.end.x - _road_size)) {
					c.tiles(x, n.begin.y + _road_size) = 'W';
					c.tiles(x, n.end.y - _road_size) = 'W';
				}
				if (y >= (n.begin.y + _road_size) && y <= (n.end.y - _road_size)) {
					c.tiles(n.begin.x + _road_size, y) = 'W';
					c.tiles(n.end.x - _road_size, y) = 'W';
				}
				//NPC
				if (x == n.begin.x && y == n.begin.y) {
					if (rand() % 100 < 50) {
						c.objects(x, y) = 'c';
					}
				}
				if (x == n.end.x && y == n.end.y) {
					if (rand() % 100 < 50) {
						c.objects(x, y) = 'p';
					}
				}



			});

			switch (rand() % 4)
			{
			case 0:
				for (int i = n.center.x; i < n.end.x; i++) {
					c.tiles(i, n.center.y) = 'l';
				}
				break;
			case 1:
				for (int i = n.center.x; i > n.begin.x; i--) {
					c.tiles(i, n.center.y) = 'l';
				}
				break;
			case 2:
				for (int i = n.center.y; i < n.end.y; i++) {
					c.tiles(n.center.x, i) = 'l';
				}
				break;
			case 3:
				for (int i = n.center.y; i > n.begin.y; i--) {
					c.tiles(n.center.x, i) = 'l';
				}
				break;
			}
		}
	};
}

#endif

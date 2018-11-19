#ifndef _GENERATE_PARK_H
#define _GENERATE_PARK_H
#include "Fill.h"

namespace generate::strategy::bsp {
	class Park : public Fill {
	private:
		int _iterations;
	public:
		Park(int iterations) : _iterations(iterations) {};
		~Park() = default;
		void write(models::City& c, const Node& n) const override {
			for (int x = n.begin.x; x <= n.end.x; x++)
				for (int y = n.begin.y; y <= n.end.y; y++) {
					c(x, y) = '-';
					if ((x > n.begin.x && x < n.end.x - 1) && (y > n.begin.y && y < n.end.y - 1))
						c(x, y) = 'g';
				}

			int x = n.center.x;
			int y = n.center.y;
			for (int i = 0; i < _iterations; i++)
			{
				c(x, y) = 'w';
				switch (rand() % 4)
				{
				case 0:
					if (x > n.begin.x + 1)
						x--;
					break;
				case 1:
					if (x < (n.end.x - 2))
						x++;
					break;
				case 2:
					if (y > n.begin.y + 1)
						y--;
					break;
				case 3:
					if (y < (n.end.y - 2))
						y++;
					break;
				}
			}
		}
	};
}

#endif

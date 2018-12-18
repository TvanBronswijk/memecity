#ifndef _GENERATE_PREFAB_H
#define _GENERATE_PREFAB_H
#include "Fill.h"

namespace generate::strategy::bsp {
	class Prefab : public Fill {
	private:
		const models::Prefab& _prefab;
	public:
		Prefab(const models::Prefab& prefab) : _prefab(prefab) {}
		~Prefab() = default;
		void write(models::City& c, const Node& n) const override {
			iterate(n, [&](int x, int y) {
				int xoff = x - n.x;
				int yoff = y - n.y;
				c.tiles(y, x) = xoff < _prefab.width && yoff < _prefab.height ? _prefab.tiles(xoff, yoff) : '-';
				c.objects(y, x) = xoff < _prefab.width && yoff < _prefab.height ? _prefab.objects(xoff, yoff) : '\0';
			});
		}
	};
}

#endif

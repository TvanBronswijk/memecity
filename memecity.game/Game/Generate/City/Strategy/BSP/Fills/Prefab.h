#ifndef _GENERATE_PREFAB_H
#define _GENERATE_PREFAB_H
#include "Fill.h"

namespace generate::strategy::bsp {
	class Prefab : public Fill {
	private:
		models::Prefab& _prefab;
	public:
		Prefab(models::Prefab& prefab) : _prefab(prefab) {}
		~Prefab() = default;
		void write(models::City& c, const Node& n) const override {
			iterate(n, [&](int x, int y) {
				c.tiles(x, y) = _prefab.tiles(x - n.x, y - n.y);
				c.objects(x, y) = _prefab.objects(x - n.x, y - n.y);
			});
		}
	};
}

#endif

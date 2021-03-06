#ifndef _GENERATE_EMPTY_H
#define _GENERATE_EMPTY_H
#include "Fill.h"

namespace generate::strategy::bsp {
	class Empty : public Fill {
	private:
		char _c;
	public:
		Empty() : Empty('-') {}
		Empty(char c) : _c(c) {}
		~Empty() = default;
		void write(models::City& c, const Node& n) const override {
			const char* garbage = " ";
			iterate(n, [&](int x, int y) {c.tiles(x, y) = _c; c.objects(x, y) = garbage[x*n.h+y]; });
		}
	};
}

#endif





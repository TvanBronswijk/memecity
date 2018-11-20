#ifndef _GENERATE_FILL_H
#define _GENERATE_FILL_H
#include <functional>
#include "..\BSP.h"

namespace generate::strategy::bsp {
	enum Fills {
		building, park, empty, prefab
	};

	class Fill {
	protected:
		virtual void iterate(const Node& n, std::function<void(int, int)> func) const {
			for (int x = n.begin.x; x <= n.end.x; x++) {
				for (int y = n.begin.y; y <= n.end.y; y++) {
					func(x, y);
				}
			}
		}
	public:
		Fill() = default;
		Fill(const Fill &) = delete;
		Fill(Fill &&) = delete;
		Fill& operator=(const Fill&) = delete;
		Fill& operator=(Fill&&) = delete;
		virtual ~Fill() = default;
		virtual void write(models::City& c, const Node& n) const = 0;
	};
}

#endif

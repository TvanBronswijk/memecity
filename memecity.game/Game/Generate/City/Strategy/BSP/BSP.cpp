#include "BSP.h"
#include <ctime>
#include <algorithm>
#include <random>
#include "Fills\Fill.h"
#include "Fills\Building.h"
#include "Fills\Park.h"
#include "Fills\Empty.h"
#include "Fills\Prefab.h"

namespace generate::strategy::bsp {
	std::map<Fills, int> fill_chance{
		{building, 75},
		{park, 15},
		{empty, 10}

	};

	models::City BSP::generate(int w, int h)
	{
		srand(time(nullptr));
		Node root = { 1, 1, w, h };
		split_recursively(root, root.horizontal());

		auto nodes = root.get_leaves();
		models::City city = { w, h };
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				city.tiles(x, y) = 'W';
				city.objects(x, y) = '\0';
			}
		}
		for (int x = 1; x < w - 1; x++) {
			for (int y = 1; y < h - 1; y++) {
				city.tiles(x, y) = '-';
			}
		}

		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(nodes), std::end(nodes), rng);
		for (auto& node : nodes)
		{
			this->write_node(city, node);
		}
		city.start.x = nodes.back().get().center.x;
		city.start.y = nodes.back().get().center.y;
		return std::move(city);
	}

	void BSP::split_recursively(Node& n, bool horizontal) const
	{
		if (n.split(MIN_NODE_WIDTH, MIN_NODE_HEIGHT, horizontal)
			|| ((n.w > MIN_NODE_WIDTH * 5 || n.h > MIN_NODE_HEIGHT * 5) && n.split(MIN_NODE_WIDTH, MIN_NODE_HEIGHT, !horizontal))) {
			split_recursively(n.left(), !n.horizontal() && !(rand() % 16 == 0));
			split_recursively(n.right(), !n.horizontal() && !(rand() % 16 == 0));
		}
	}


	bool fits(const models::Prefab& pf, const Node& n) {
		return pf.width <= n.w && pf.height <= n.h;
	}

	Fills get_random_fill() {
		int r = rand() % 100;
		int i = 0;
		Fills choice;
		for (auto& chance : fill_chance) {
			i += chance.second;
			if (i >= r) {
				choice = chance.first;
				break;
			}
		}
		return choice;
	}

	void BSP::write_node(models::City &c, const Node& n)
	{

		if (!_prefabs.empty()) {
			auto prefab = _prefabs.front();
			if (_prefabs.size() > 0 && fits(*prefab, n)) {
				Prefab(*prefab).write(c, n);
				_prefabs.pop();
			}
			else {
				switch (get_random_fill()) {
				case building:
					Building().write(c, n);
					break;
				case park:
					Park(n.w + n.h).write(c, n);
					break;
				case empty:
					Empty('-').write(c, n);
					break;
				}
			}
		}
	}
}


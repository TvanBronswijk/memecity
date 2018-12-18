#include "BSP.h"
#include <ctime>
#include "Fills\Fill.h"
#include "Fills\Building.h"
#include "Fills\Park.h"
#include "Fills\Empty.h"
#include "Fills\Prefab.h"

namespace generate::strategy::bsp {
	std::map<Fills, int> fill_chance {
		{building, 75},
		{park, 10},
		{empty, 10},
		{prefab, 5}
	};

	models::City BSP::generate(int w, int h)
	{
		srand(time(nullptr));
		Node root = { 0, 0, w, h };
		split_recursively(root, root.horizontal());

		auto nodes = root.get_leaves();
		models::City city = { w, h };
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				city.tiles(x, y) = '-';
				city.objects(x, y) = '\0';
			}
		}
		for (auto& node : nodes)
		{
			this->write_node(city, node);
		}
		city.start.x = nodes.front().get().center.x;
		city.start.y = nodes.front().get().center.y;
		return std::move(city);
	}

	void BSP::split_recursively(Node& n, bool horizontal) const
	{
		if (n.split(MIN_NODE_WIDTH, MIN_NODE_HEIGHT, horizontal) 
			|| ((n.w > MIN_NODE_WIDTH*5 || n.h > MIN_NODE_HEIGHT*5) && n.split(MIN_NODE_WIDTH, MIN_NODE_HEIGHT, !horizontal))) {
			split_recursively(n.left(), !n.horizontal() && !(rand() % 16 == 0));
			split_recursively(n.right(), !n.horizontal() && !(rand() % 16 == 0));
		}
	}

	void BSP::write_node(models::City &c, const Node& n)
	{
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
		if (choice == building) {
			Building().write(c, n);
		}
		else if (choice == park) {
			Park(n.w + n.h).write(c, n);
		}
		else if (choice == empty) {
			Empty('-').write(c, n);
		}
		else if (choice == prefab) {
			auto prefab = get_next_prefab();
			if (prefab != nullptr) {
				Prefab(*prefab).write(c, n);
			}
		}
		else {
			return;
		}
	}
}


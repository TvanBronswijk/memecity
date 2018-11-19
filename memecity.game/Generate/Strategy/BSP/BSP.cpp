#include "BSP.h"
#include <ctime>

namespace generate::strategy::bsp {
	models::City BSP::generate(int w, int h) const
	{
		srand(time(nullptr));
		Node root = { 0, 0, w, h };

		if (rand() % 2 == 0)
			this->split_h(root);
		else
			this->split_v(root);

		auto nodes = root.get_leaves();
		models::City city = { w, h };
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
				city.coord(x, y) = '-';
		for (auto node : nodes)
		{
			this->fill_node(city, *node);
		}
		return std::move(city);
	}

	void BSP::split_h(Node& n) const
	{
		if (n.h <= this->MIN_NODE_HEIGHT*2)
			return;

		int split = this->MIN_NODE_HEIGHT + (rand() % (n.h - (this->MIN_NODE_HEIGHT*2)));
		n.left = new Node(n.begin.x, n.begin.y, n.w, split);
		n.right = new Node(n.begin.x, n.left->end.y, n.w, n.h - split);

		this->split_v(*n.left);
		this->split_v(*n.right);
	}

	void BSP::split_v(Node& n) const
	{
		if (n.w <= this->MIN_NODE_WIDTH*2)
			return;

		int split = this->MIN_NODE_WIDTH + (rand() % (n.w - (this->MIN_NODE_WIDTH*2)));
		n.left = new Node(n.begin.x, n.begin.y, split, n.h);
		n.right = new Node(n.left->end.x, n.begin.y, n.w - split, n.h);

		this->split_h(*n.left);
		this->split_h(*n.right);
	}

	void BSP::fill_node(models::City &c, const Node& n) const
	{
		int r = rand() % 100;
		if (r > 90)
			fill_empty(c, n);
		else if (r > 60)
			fill_water(c, n);
		else
			fill_building(c, n);
	}

	void BSP::fill_building(models::City &c, const Node& n) const
	{
		int r_size = 1;
		for (int x = n.begin.x; x <= n.end.x; x++)
			for (int y = n.begin.y; y <= n.end.y; y++) {
				c.coord(x, y) = '-';
				if (x >= (n.begin.x + r_size) && x <= (n.end.x - r_size)) {
					c.coord(x, n.begin.y + r_size) = 'W';
					c.coord(x, n.end.y - r_size) = 'W';
				}
				if (y >= (n.begin.y + r_size) && y <= (n.end.y - r_size)) {
					c.coord(n.begin.x + r_size, y) = 'W';
					c.coord(n.end.x - r_size, y) = 'W';
				}
			}

		switch (rand() % 4)
		{
		case 0:
			for (int i = n.center.x; i < n.end.x; i++)
				c.coord(i, n.center.y) = '-';
			break;
		case 1:
			for (int i = n.center.x; i > n.begin.x; i--)
				c.coord(i, n.center.y) = '-';
			break;
		case 2:
			for (int i = n.center.y; i < n.end.y; i++)
				c.coord(n.center.x, i) = '-';
			break;
		case 3:
			for (int i = n.center.y; i > n.begin.y; i--)
				c.coord(n.center.x, i) = '-';
			break;
		}

	}

	void BSP::fill_water(models::City &c, const Node& n) const
	{
		int WATER_GEN = this->MIN_NODE_HEIGHT * 2 + this->MIN_NODE_WIDTH * 2;
		for (int x = n.begin.x; x <= n.end.x; x++)
			for (int y = n.begin.y; y <= n.end.y; y++) {
				c.coord(x, y) = '-';
				if ((x > n.begin.x && x < n.end.x - 1) && (y > n.begin.y && y < n.end.y - 1))
					c.coord(x, y) = 'g';
			}

		int x = n.center.x;
		int y = n.center.y;
		for (int i = 0; i < WATER_GEN; i++)
		{
			c.coord(x, y) = 'w';
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

	void BSP::fill_empty(models::City &c, const Node& n) const
	{
		for (int x = n.begin.x; x <= n.end.x; x++)
			for (int y = n.begin.y; y <= n.end.y; y++)
				c.coord(x, y) = '-';
	}

	void BSP::fill_prefab(models::City &c, const Node& n) const
	{
	}
}


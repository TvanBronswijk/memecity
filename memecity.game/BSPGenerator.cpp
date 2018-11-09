#include "BSPGenerator.h"

std::unique_ptr<generate::models::City> generate::strategy::bsp::BSPGenerator::generate(int w, int h)
{
	srand(time(0));
	generate::strategy::bsp::Node* root = new generate::strategy::bsp::Node(0, 0, w, h);

	if (rand() % 2 == 0)
		this->split_h(root);
	else
		this->split_v(root);

	auto nodes = this->get_leaves(root);
	auto city = std::make_unique<generate::models::City>(w, h);
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			city->coord(x, y) = '-';
	for(auto node : nodes)
	{
		this->fill_node(node, city);
	}
	delete root;
	return city;
}

void generate::strategy::bsp::BSPGenerator::split_h(generate::strategy::bsp::Node* n)
{
	if (n->h - this->MIN_NODE_HEIGHT < this->MIN_NODE_HEIGHT)
		return;
	
	int split = this->MIN_NODE_HEIGHT + rand() % (n->h - this->MIN_NODE_HEIGHT);
	n->left =	new generate::strategy::bsp::Node(n->x, n->y,		n->w, split);
	n->right =	new generate::strategy::bsp::Node(n->x, n->left->y2, n->w, n->h - split);

	this->split_v(n->left);
	this->split_v(n->right);
}

void generate::strategy::bsp::BSPGenerator::split_v(generate::strategy::bsp::Node* n)
{
	if (n->w - this->MIN_NODE_WIDTH < this->MIN_NODE_WIDTH)
		return;

	int split = this->MIN_NODE_WIDTH + (rand() % (n->w - this->MIN_NODE_WIDTH));
	n->left =	new generate::strategy::bsp::Node(n->x,			n->y, split,		n->h);
	n->right =	new generate::strategy::bsp::Node(n->left->x2,	n->y, n->w - split, n->h);
	
	this->split_h(n->left);
	this->split_h(n->right);
}

std::vector<generate::strategy::bsp::Node*> generate::strategy::bsp::BSPGenerator::get_leaves(generate::strategy::bsp::Node* n)
{
	if (!(n->has_left() && n->has_right()))
	{
		std::vector<Node*> vect = { n };
		return vect;
	}

	auto left = this->get_leaves(n->left);
	auto right = this->get_leaves(n->right);
	left.insert(left.end(), right.begin(), right.end());
	return left;
}

void generate::strategy::bsp::BSPGenerator::fill_node(generate::strategy::bsp::Node* n, std::unique_ptr<generate::models::City> &c)
{
	int r = rand() % 100;
	if (r > 90)
		fill_empty(n, c);
	else if (r > 60)
		fill_water(n, c);
	else 
		fill_building(n, c);
}

void generate::strategy::bsp::BSPGenerator::fill_building(generate::strategy::bsp::Node * n, std::unique_ptr<generate::models::City> &c)
{
	int r_size = 1;
	for (int x = n->x; x <= n->x2; x++)
		for (int y = n->y; y <= n->y2; y++) {
			c->coord(x, y) = '-';
			if (x >= (n->x + r_size) && x <= (n->x2 - r_size)) {
				c->coord(x, n->y + r_size) = 'W';
				c->coord(x, n->y2 - r_size) = 'W';
			}
			if (y >= (n->y + r_size) && y <= (n->y2 - r_size)) {
				c->coord(n->x + r_size, y) = 'W';
				c->coord(n->x2 - r_size, y) = 'W';
			}
		}

	switch(rand() % 4)
	{
	case 0:
		for (int i = n->center_x; i < n->x2; i++)
			c->coord(i, n->center_y) = '-';
		break;
	case 1:
		for (int i = n->center_x; i > n->x; i--)
			c->coord(i, n->center_y) = '-';
		break;
	case 2:
		for (int i = n->center_y; i < n->y2; i++)
			c->coord(n->center_x, i) = '-';
		break;
	case 3:
		for (int i = n->center_y; i > n->y; i--)
			c->coord(n->center_x, i) = '-';
		break;
	}

}

void generate::strategy::bsp::BSPGenerator::fill_water(Node * n, std::unique_ptr<generate::models::City> &c)
{
	int WATER_GEN = this->MIN_NODE_HEIGHT * 2 + this->MIN_NODE_WIDTH * 2;
	for (int x = n->x; x <= n->x2; x++)
		for (int y = n->y; y <= n->y2; y++) {
			c->coord(x, y) = '-';
			if ((x > n->x && x < n->x2-1) && (y > n->y && y < n->y2-1))
				c->coord(x, y) = 'g';
		}

	int x = n->center_x;
	int y = n->center_y;
	for (int i = 0; i < WATER_GEN; i++)
	{
		c->coord(x, y) = 'w';
		switch (rand() % 4)
		{
		case 0:
			if (x > n->x+1)
				x--;
			break;
		case 1:
			if (x < (n->x2-2))
				x++;
			break;
		case 2:
			if (y > n->y+1)
				y--;
			break;
		case 3:
			if (y < (n->y2-2))
				y++;
			break;
		}
	}
}

void generate::strategy::bsp::BSPGenerator::fill_empty(generate::strategy::bsp::Node * n, std::unique_ptr<generate::models::City> &c)
{
	for (int x = n->x; x <= n->x2; x++)
		for (int y = n->y; y <= n->y2; y++)
			c->coord(x, y) = '-';
}

void generate::strategy::bsp::BSPGenerator::fill_prefab(generate::strategy::bsp::Node * n, std::unique_ptr<generate::models::City> &c)
{
}

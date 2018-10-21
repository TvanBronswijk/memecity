#ifndef _BSP_GENERATOR_H
#define _BSP_GENERATOR_H
#include <vector>
#include <iostream>
#include <time.h>
#include "GeneratorStrategy.h"

struct Node : Rectangle {
	Node *left, *right;
	Node(int x, int y, int w, int h) : Rectangle(x, y, w, h)
	{
		left = nullptr;
		right = nullptr;
	}

	bool has_left()
	{
		return left != NULL;
	}
	bool has_right()
	{
		return right != NULL;
	}
};

class BSPGenerator : GeneratorStrategy {
private:
	const static int MIN_NODE_WIDTH = 16;
	const static int MIN_NODE_HEIGHT = 16;

	void split_h(Node* n);
	void split_v(Node* n);
	std::vector<Node*> get_leaves(Node* n);
	void fill_node(Node* n, std::unique_ptr<City> &c);
	void fill_building(Node* n, std::unique_ptr<City> &c);
	void fill_water(Node* n, std::unique_ptr<City> &c);
	void fill_empty(Node* n, std::unique_ptr<City> &c);
	void fill_prefab(Node* n, std::unique_ptr<City> &c);
public:
	std::unique_ptr<City> generate(int w, int h);
};

#endif
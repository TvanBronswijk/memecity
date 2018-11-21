#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include <utility>
#include <vector>
#include <memory>
#include "BoundaryRectangle.h"

class QuadTree
{
private:
	bool _is_divided{};

	std::unique_ptr<QuadTree> _northwest;
	std::unique_ptr<QuadTree> _northeast;
	std::unique_ptr<QuadTree> _southwest;
	std::unique_ptr<QuadTree> _southeast;

	std::vector<BoundaryRectangle> _objects;
	std::size_t _capacity{};
	BoundaryRectangle _boundary;

	void subdivide();

public:
	QuadTree() : _boundary(BoundaryRectangle(0.0f, 0.0f, 0.0f, 0.0f)) {}

	QuadTree(int capacity, const BoundaryRectangle& boundary) : _capacity(capacity), _boundary(boundary) {}
	
	bool insert(const BoundaryRectangle& collider);
	std::vector<BoundaryRectangle> query(const BoundaryRectangle& range);
	void update();
};

#endif

#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include <utility>
#include <vector>
#include <memory>
#include "Engine/Collider.h"
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
	QuadTree(std::size_t capacity, BoundaryRectangle boundary) : _capacity(capacity), _boundary(std::move(boundary)) {}
	
	bool insert(const BoundaryRectangle& collider);
	std::vector<BoundaryRectangle> query(const BoundaryRectangle& range);
	void update();
};

#endif

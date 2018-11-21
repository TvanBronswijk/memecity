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

	size_t _capacity{};
	Rectangle _boundary;
	std::vector<std::reference_wrapper<const BoundaryRectangle>> _objects;

	void subdivide();

public:
	QuadTree() : _boundary(Rectangle(0.0f, 0.0f, 0.0f, 0.0f)) {}

	QuadTree(size_t capacity, Rectangle boundary)
		: _capacity(capacity), _boundary(boundary) {}
	QuadTree(size_t capacity, Rectangle boundary, std::vector<std::reference_wrapper<const BoundaryRectangle>> boundary_rectangles)
		: _capacity(capacity), _boundary(boundary), _objects(std::move(boundary_rectangles)) {}

	bool insert(const BoundaryRectangle& collider);
	std::vector<std::reference_wrapper<const BoundaryRectangle>> query(const BoundaryRectangle& range);
};

#endif

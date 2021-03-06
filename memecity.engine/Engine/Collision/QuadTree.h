#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include <utility>
#include <vector>
#include <memory>
#include "..\Util\Rectangle.h"
#include "BoundaryRectangle.h"

class QuadTree
{
private:
	bool _is_divided{};

	std::unique_ptr<QuadTree> _northwest;
	std::unique_ptr<QuadTree> _northeast;
	std::unique_ptr<QuadTree> _southwest;
	std::unique_ptr<QuadTree> _southeast;

	size_t _capacity;
	Rectangle _boundary;
	std::vector<const BoundaryRectangle*> _objects;

	void subdivide();

public:
	QuadTree() : _boundary(Rectangle(0.0f, 0.0f, 0.0f, 0.0f)) {}

	QuadTree(size_t capacity, Rectangle boundary)
		: _capacity(capacity), _boundary(boundary) {
		_objects.reserve(capacity + 1);
	}
	QuadTree(size_t capacity, Rectangle boundary, std::vector<const BoundaryRectangle*> boundary_rectangles)
		: _capacity(capacity), _boundary(boundary), _objects(std::move(boundary_rectangles)) {
		_objects.reserve(capacity + 1);
	}
	~QuadTree() = default;

	bool insert(const BoundaryRectangle& collider);
	void query(const BoundaryRectangle& range, std::vector<std::reference_wrapper<const BoundaryRectangle>> &found_object);
	void clear();
};

#endif

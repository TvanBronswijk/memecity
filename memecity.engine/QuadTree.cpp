#include "QuadTree.h"
#include <algorithm>

void QuadTree::subdivide()
{
	const auto x = this->_boundary.x;
	const auto y = this->_boundary.y;
	const auto half_w = this->_boundary.w / 2;
	const auto half_h = this->_boundary.h / 2;

	auto nw = Rectangle(x, y, half_w, half_h);
	this->_northwest = std::make_unique<QuadTree>(_capacity, nw);
	query({ nw.x, nw.y, nw.w, nw.h }, _northwest->_objects);

	auto ne = Rectangle(x + half_w, y, half_w, half_h);
	this->_northeast = std::make_unique<QuadTree>(_capacity, ne);
	query({ ne.x, ne.y, ne.w, ne.h }, _northeast->_objects);

	auto sw = Rectangle(x, y + half_h, half_w, half_h);
	this->_southwest = std::make_unique<QuadTree>(_capacity, sw);
	query({ sw.x, sw.y, sw.w, sw.h }, _southwest->_objects);

	auto se = Rectangle(x + half_w, y + half_h, half_w, half_h);
	this->_southeast = std::make_unique<QuadTree>(_capacity, se);
	query({ se.x, se.y, se.w, se.h }, _southeast->_objects);
	
	this->_is_divided = true;
}

bool QuadTree::insert(const BoundaryRectangle& collider)
{
	if (!intersects(_boundary, collider))
	{
		return false;
	}

	if (this->_objects.size() < this->_capacity) {
		this->_objects.push_back(&collider);
	}
	else if (!this->_is_divided)
	{
		this->subdivide();
	}

	if (this->_is_divided)
	{
		if (this->_northeast->insert(collider))
		{
		}
		else if (this->_northwest->insert(collider))
		{
		}
		else if (this->_southeast->insert(collider))
		{
		}
		else if (this->_southwest->insert(collider))
		{
		}
	}

	return true;
}

void QuadTree::query(const BoundaryRectangle& range, std::vector<const BoundaryRectangle*> &found_objects)
{
	if (!intersects(_boundary, range))
	{
		return;
	}

	if (this->_is_divided)
	{
		this->_northeast->query(range, found_objects);
		this->_northwest->query(range, found_objects);
		this->_southeast->query(range, found_objects);
		this->_southwest->query(range, found_objects);
	}
	else
	{
		copy(_objects.begin(), _objects.end(), std::back_inserter(found_objects));
	}
}
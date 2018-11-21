#include "QuadTree.h"

void QuadTree::subdivide()
{
	const auto x = this->_boundary.x;
	const auto y = this->_boundary.y;
	const auto half_w = this->_boundary.w / 2;
	const auto half_h = this->_boundary.h / 2;

	auto nw = Rectangle(x, y, half_w, half_h);
	auto nw_objects = query({ nw.x, nw.y, nw.w, nw.h });
	this->_northwest = std::make_unique<QuadTree>(_capacity, nw, nw_objects);

	auto ne = Rectangle(x + half_w, y, half_w, half_h);
	auto ne_objects = query({ ne.x, ne.y, ne.w, ne.h });
	this->_northeast = std::make_unique<QuadTree>(_capacity, ne, ne_objects);

	auto sw = Rectangle(x, y + half_h, half_w, half_h);
	auto sw_objects = query({ sw.x, sw.y, sw.w, sw.h });
	this->_southwest = std::make_unique<QuadTree>(_capacity, sw, sw_objects);

	auto se = Rectangle(x + half_w, y + half_h, half_w, half_h);
	auto se_objects = query({ se.x, se.y, se.w, se.h });
	this->_southeast = std::make_unique<QuadTree>(_capacity, se, se_objects);

	this->_is_divided = true;
}

bool QuadTree::insert(const BoundaryRectangle& collider)
{
	if (!contains(_boundary, collider))
	{
		return false;
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
		return true;
	}
	else
	{
		if (this->_objects.size() < this->_capacity)
		{
			this->_objects.push_back(std::ref(collider));
			return true;
		}
		else
		{
			this->subdivide();
			return this->insert(collider);
		}
	}
}

std::vector<std::reference_wrapper<const BoundaryRectangle>> QuadTree::query(const BoundaryRectangle& range)
{
	std::vector<std::reference_wrapper<const BoundaryRectangle>> found_objects;

	if (!intersects(_boundary, range))
	{
		return found_objects;
	}

	if (this->_is_divided)
	{
		auto temp = this->_northeast->query(range);
		found_objects.insert(found_objects.begin(), temp.begin(), temp.end());

		temp = this->_northwest->query(range);
		found_objects.insert(found_objects.begin(), temp.begin(), temp.end());

		temp = this->_southeast->query(range);
		found_objects.insert(found_objects.begin(), temp.begin(), temp.end());

		temp = this->_southwest->query(range);
		found_objects.insert(found_objects.begin(), temp.begin(), temp.end());
	}
	else
	{
		return _objects;
	}

	return found_objects;
}
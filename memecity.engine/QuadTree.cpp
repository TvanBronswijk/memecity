#include "QuadTree.h"

void QuadTree::subdivide()
{
	const auto x = this->_boundary.x;
	const auto y = this->_boundary.y;
	const auto w = this->_boundary.w / 2;
	const auto h = this->_boundary.h / 2;

	auto nw = BoundaryRectangle(x + w, y - h, w, h);
	this->_northwest = std::make_unique<QuadTree>(_capacity, nw);

	auto ne = BoundaryRectangle(x - w, y - h, w, h);
	this->_northeast = std::make_unique<QuadTree>(_capacity, ne);

	auto sw = BoundaryRectangle(x + w, y + h, w, h);
	this->_southwest = std::make_unique<QuadTree>(_capacity, sw);

	auto se = BoundaryRectangle(x - w, y + h, w, h);
	this->_southeast = std::make_unique<QuadTree>(_capacity, se);

	this->_is_divided = true;
}

bool QuadTree::insert(const BoundaryRectangle& collider)
{
	if (!this->_boundary.contains(collider))
	{
		return false;
	}

	if (this->_objects.size() < this->_capacity)
	{
		this->_objects.push_back(collider);
		return true;
	}

	if (!this->_is_divided)
	{
		this->subdivide();
	}

	if (this->_northeast->insert(collider))
	{
		return true;
	}
	if (this->_northwest->insert(collider))
	{
		return true;
	}
	if (this->_southeast->insert(collider))
	{
		return true;
	}
	if (this->_southwest->insert(collider))
	{
		return true;
	}

	return false;
}

std::vector<BoundaryRectangle> QuadTree::query(const BoundaryRectangle& range)
{
	auto found_objects = std::vector<BoundaryRectangle>();

	if (!this->_boundary.intersects(range))
	{
		return found_objects;
	}

	for (const auto& object : _objects)
	{
		if (range.contains(object))
		{
			found_objects.push_back(object);
		}
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

	return found_objects;
}

void QuadTree::update()
{

}

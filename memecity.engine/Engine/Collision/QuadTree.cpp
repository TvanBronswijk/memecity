#include "QuadTree.h"
#include <algorithm>

void QuadTree::subdivide()
{
	const auto x = this->_boundary.x;
	const auto y = this->_boundary.y;
	const auto half_w = this->_boundary.w / 2;
	const auto half_h = this->_boundary.h / 2;

	if (!this->_northwest) this->_northwest = std::make_unique<QuadTree>(_capacity, Rectangle(x, y, half_w, half_h));
	if (!this->_northeast) this->_northeast = std::make_unique<QuadTree>(_capacity, Rectangle(x + half_w, y, half_w, half_h));
	if (!this->_southwest) this->_southwest = std::make_unique<QuadTree>(_capacity, Rectangle(x, y + half_h, half_w, half_h));
	if (!this->_southeast) this->_southeast = std::make_unique<QuadTree>(_capacity, Rectangle(x + half_w, y + half_h, half_w, half_h));
	
	for (auto& obj : _objects) {
		if (intersects(*obj, _northwest->_boundary)) {
			_northwest->_objects.push_back(obj);
		}
		else if (intersects(*obj, _northeast->_boundary)) {
			_northeast->_objects.push_back(obj);
		}
		else if (intersects(*obj, _southwest->_boundary)) {
			_southwest->_objects.push_back(obj);
		}
		else if (intersects(*obj, _southeast->_boundary)) {
			_southeast->_objects.push_back(obj);
		}
	}
	_objects.clear();

	this->_is_divided = true;
}

bool QuadTree::insert(const BoundaryRectangle& collider)
{
	if (intersects(_boundary, collider))
	{
		if (!this->_is_divided) {
			if (this->_objects.size() < this->_capacity) {
				this->_objects.push_back(&collider);
			}
			else {
				this->subdivide();
			}
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
	return false;
}

void QuadTree::query(const BoundaryRectangle& range, std::vector<std::reference_wrapper<const BoundaryRectangle>> &found_objects)
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
		std::transform(_objects.begin(), _objects.end(), std::back_inserter(found_objects), 
			[](auto& obj)->std::reference_wrapper<const BoundaryRectangle> {return std::ref(*obj); });
	}
}

void QuadTree::clear()
{
	if (this->_is_divided) {
		this->_northeast->clear();
		this->_northwest->clear();
		this->_southeast->clear();
		this->_southwest->clear();
		this->_is_divided = false;
	}
	this->_objects.clear();
	this->_objects.reserve(_capacity);
}

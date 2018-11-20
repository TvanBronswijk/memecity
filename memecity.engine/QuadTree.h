#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include <vector>
#include <memory>
#include "Engine/Collider.h"

template <class T>
class QuadTree
{
private:
	bool _is_divided;

	std::unique_ptr<QuadTree> _northwest;
	std::unique_ptr<QuadTree> _northeast;
	std::unique_ptr<QuadTree> _southwest;
	std::unique_ptr<QuadTree> _southeast;

	std::vector<T> _objects;
	Collider _boundary;
	std::size_t _capacity;

	void subdivide()
	{
		auto x = this->_boundary.x;
		auto y = this->_boundary.y;
		auto w = this->_boundary.w;
		auto h = this->_boundary.h;

		auto nw = Collider(x + (w / 2), y - (h / 2), (w / 2), (h / 2));
		this->_northwest = std::make_unique<QuadTree>(nw, _capacity);

		auto ne = Collider(x - (w / 2), y - (h / 2), (w / 2), (h / 2));
		this->_northeast = std::make_unique<QuadTree>(ne, _capacity);

		auto sw = Collider(x + (w / 2), y + (h / 2), (w / 2), (h / 2));
		this->_southwest = std::make_unique<QuadTree>(sw, _capacity);

		auto se = Collider(x - (w / 2), y + (h / 2), (w / 2), (h / 2));
		this->_southeast = std::make_unique<QuadTree>(se, _capacity);

		this->_is_divided = true;
	}

public:
	QuadTree(T &object, const std::size_t capacity, const Collider &boundary) : _is_divided(false), _boundary(boundary), _capacity(capacity) {}
	
	bool insert(const T& object)
	{
		if (!this->_boundary.contains(object))
		{
			return false;
		}

		if (this->_objects.size() < this->_capacity)
		{
			this->_objects.push_back(object);
			return true;
		}

		if (!this->_is_divided)
		{
			this->subdivide();
		}

		if (this->_northeast->insert(object))
		{
			return true;
		}
		if (this->_northwest->insert(object))
		{
			return true;
		}
		if (this->_southeast->insert(object))
		{
			return true;
		}
		if (this->_southwest->insert(object))
		{
			return true;
		}

		return false;
	}

	std::vector<Collider> query(T& range)
	{
		std::vector<T> found_objects;

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
			found_objects.insert(found_objects.begin(), this->_northeast->query(range).begin(), this->_northeast->query(range).end());
			found_objects.insert(found_objects.begin(), this->_northwest->query(range).begin(), this->_northwest->query(range).end());
			found_objects.insert(found_objects.begin(), this->_southeast->query(range).begin(), this->_southeast->query(range).end());
			found_objects.insert(found_objects.begin(), this->_southwest->query(range).begin(), this->_southwest->query(range).end());
		}

		return found_objects;
	}
};

#endif

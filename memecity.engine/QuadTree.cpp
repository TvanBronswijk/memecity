#include "QuadTree.h"

bool QuadTree::insert(const Rectangle& rectangle)
{
	if (!this->boundary.contains(rectangle))
	{
		return false;
	}

	if (this->rectangles.size() < this->capacity)
	{
		this->rectangles.push_back(rectangle);
		return true;
	}
	if (!this->is_divided)
	{
		this->subdivide();
	}

	if (this->northeast->insert(rectangle))
	{
		return true;
	}
	if (this->northwest->insert(rectangle))
	{
		return true;
	}
	if (this->southeast->insert(rectangle))
	{
		return true;
	}
	if (this->southwest->insert(rectangle))
	{
		return true;
	}

	return false;
}

std::vector<Rectangle> QuadTree::query(Rectangle& range)
{
	std::vector<Rectangle> found_rectangles;

	if (!this->boundary.intersects(range))
	{
		return found_rectangles;
	}

	for (const auto& rectangle : rectangles)
	{
		if (range.contains(rectangle))
		{
			found_rectangles.push_back(rectangle);
		}
	}

	if (this->is_divided)
	{
		found_rectangles.insert(found_rectangles.begin(), this->northeast->query(range).begin(), this->northeast->query(range).end());
		found_rectangles.insert(found_rectangles.begin(), this->northwest->query(range).begin(), this->northwest->query(range).end());
		found_rectangles.insert(found_rectangles.begin(), this->southeast->query(range).begin(), this->southeast->query(range).end());
		found_rectangles.insert(found_rectangles.begin(), this->southwest->query(range).begin(), this->southwest->query(range).end());
	}

	return found_rectangles;
}

void QuadTree::subdivide()
{
	auto x = this->boundary.x;
	auto y = this->boundary.y;
	auto w = this->boundary.w;
	auto h = this->boundary.h;

	auto nw = Rectangle(x + (w / 2), y - (h / 2), (w / 2), (h / 2));
	this->northwest = std::make_unique<QuadTree>(nw, capacity);
	auto ne = Rectangle(x - (w / 2), y - (h / 2), (w / 2), (h / 2));
	this->northeast = std::make_unique<QuadTree>(ne, capacity);
	auto sw = Rectangle(x + (w / 2), y + (h / 2), (w / 2), (h / 2));
	this->southwest = std::make_unique<QuadTree>(sw, capacity);
	auto se = Rectangle(x - (w / 2), y + (h / 2), (w / 2), (h / 2));
	this->southeast = std::make_unique<QuadTree>(se, capacity);
	this->is_divided = true;
}

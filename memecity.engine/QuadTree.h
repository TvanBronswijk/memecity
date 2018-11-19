#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H
#include <vector>
#include <memory>
#include "Engine/Textures/Texture.h"

class QuadTree
{
public:
	QuadTree(Rectangle &rectangle, size_t capacity) : is_divided(false), boundary(rectangle), capacity(capacity) {}
	bool insert(const Rectangle& rectangle);

private:
	bool is_divided;

	std::unique_ptr<QuadTree> northwest;
	std::unique_ptr<QuadTree> northeast;
	std::unique_ptr<QuadTree> southwest;
	std::unique_ptr<QuadTree> southeast;

	std::vector<Rectangle> rectangles;
	std::vector<Rectangle> query(Rectangle& range);
	Rectangle boundary;
	size_t capacity;

	void subdivide();
};

#endif
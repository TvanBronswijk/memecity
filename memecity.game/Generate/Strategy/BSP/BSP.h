#ifndef _BSP_GENERATOR_H
#define _BSP_GENERATOR_H
#include <functional>
#include <vector>
#include <iostream>
#include <map>
#include "..\Strategy.h"

namespace generate::strategy::bsp {
	struct Node : public generate::models::Rectangle {
	private:
		std::unique_ptr<Node> _left, _right;
		bool _horizontal;
	public:
		Node(int x, int y, int w, int h)
			: Rectangle(x, y, w, h), _left(nullptr), _right(nullptr), _horizontal(false) {}
		Node& left() const { return *_left;  }
		Node& right() const { return *_right;  }
		bool horizontal() const { return _horizontal; }
		std::vector<std::reference_wrapper<const Node>> get_leaves() const
		{
			if (_left == nullptr && _right == nullptr) {
				return { std::ref(*this) };
			}
			auto left_leaves = _left->get_leaves();
			auto right_leaves = _right->get_leaves();
			left_leaves.insert(left_leaves.end(), right_leaves.begin(), right_leaves.end());
			return left_leaves;
		}
		bool split(int min_width, int min_height, bool horizontal) 
		{
			this->_horizontal = horizontal;
			if (horizontal && h > min_height * 2) {
				int split = min_height + (rand() % (h - (min_height * 2)));
				_left = std::make_unique<Node>(begin.x, begin.y, w, split);
				_right = std::make_unique<Node>(begin.x, _left->end.y, w, h - split);
			}
			else if (!horizontal && w > min_width * 2) {
				int split = min_width + (rand() % (this->w - (min_width * 2)));
				_left = std::make_unique<Node>(begin.x, begin.y, split, h);
				_right = std::make_unique<Node>(_left->end.x, begin.y, w - split, h);
			} 
			else {
				return false;
			}
			return true;
		}
		~Node() = default;
	};

	class BSP : public generate::strategy::Strategy {
	private:
		const static int MIN_NODE_WIDTH = 8;
		const static int MIN_NODE_HEIGHT = 8;

		void split_recursively(Node& n, bool h) const;
		void write_node(generate::models::City &c, const Node& n);
	public:
		BSP() = default;
		BSP(std::vector<models::Prefab> prefabs) : Strategy(prefabs) {}
		~BSP() = default;
		generate::models::City generate(int w, int h) override;
	};
}


#endif

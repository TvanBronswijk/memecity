#ifndef _BSP_GENERATOR_H
#define _BSP_GENERATOR_H
#include <vector>
#include <iostream>
#include <time.h>
#include "..\Strategy.h"

namespace generate {
	namespace strategy {
		namespace bsp {
			struct Node : public generate::models::Rectangle {
				Node *left, *right;
				Node(int x, int y, int w, int h)
					: Rectangle(x, y, w, h), left(nullptr), right(nullptr) {}

				bool has_left() const { return left != nullptr; }
				bool has_right() const { return right != nullptr; }
				std::vector<const Node*> get_leaves() const 
				{
					if (!has_left() && !has_right())
						return { this };
					std::vector<const Node*> left_leaves = left->get_leaves();
					std::vector<const Node*> right_leaves = right->get_leaves();
					left_leaves.insert(left_leaves.end(), right_leaves.begin(), right_leaves.end());
					return left_leaves;
				}
				~Node()
				{
					delete left;
					delete right;
				}
			};

			class BSP : public generate::strategy::Strategy {
			private:
				const static int MIN_NODE_WIDTH = 8;
				const static int MIN_NODE_HEIGHT = 8;

				void split_h(Node& n) const;
				void split_v(Node& n) const;
				void fill_node(generate::models::City &c, const Node& n) const;
				void fill_building(generate::models::City &c, const Node& n) const;
				void fill_water(generate::models::City &c, const Node& n) const;
				void fill_empty(generate::models::City &c, const Node& n) const;
				void fill_prefab(generate::models::City &c, const Node& n) const;
			public:
				generate::models::City generate(int w, int h) const override;
			};
		}
	}
}


#endif

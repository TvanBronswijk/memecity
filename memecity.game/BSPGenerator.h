#ifndef _BSP_GENERATOR_H
#define _BSP_GENERATOR_H
#include <vector>
#include <iostream>
#include <time.h>
#include "GeneratorStrategy.h"

namespace generate {
	namespace strategy {
		namespace bsp {
			struct Node : public generate::models::Rectangle {
				Node *left, *right;
				Node(int x, int y, int w, int h)
					: Rectangle(x, y, w, h), left(nullptr), right(nullptr) {}

				bool has_left() { return left != nullptr; }
				bool has_right() { return right != nullptr; }

				~Node()
				{
					delete left;
					delete right;
				}
			};

			class BSPGenerator : public GeneratorStrategy {
			private:
				const static int MIN_NODE_WIDTH = 8;
				const static int MIN_NODE_HEIGHT = 8;

				void split_h(Node* n);
				void split_v(Node* n);
				std::vector<Node*> get_leaves(Node* n);
				void fill_node(Node* n, std::unique_ptr<generate::models::City> &c);
				void fill_building(Node* n, std::unique_ptr<generate::models::City> &c);
				void fill_water(Node* n, std::unique_ptr<generate::models::City> &c);
				void fill_empty(Node* n, std::unique_ptr<generate::models::City> &c);
				void fill_prefab(Node* n, std::unique_ptr<generate::models::City> &c);
			public:
				std::unique_ptr<generate::models::City> generate(int w, int h);
			};
		}
	}
}


#endif

#include <iostream>

struct Component {
	int entity_id;
	virtual std::string getType();
};
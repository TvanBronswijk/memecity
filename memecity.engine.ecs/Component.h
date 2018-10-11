#include <iostream>

struct Component {
	int entity_id;
	
	///<summary>Get the type of the component for filtering.</summary>
	virtual std::string get_type();
};
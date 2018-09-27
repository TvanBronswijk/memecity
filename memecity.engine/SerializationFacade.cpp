#include "SerializationFacade.h"
#include "json.hpp"

std::string SerializationFacade::serialize_example_guy(ExampleGuy& guy)
//make sure that you add SerializationFacade as a friend class in the class you want to serialize, an example of how to do this is ExampleGuy
{
	nlohmann::json j_object = { 
		{"guy", {
			"age", guy.age }
		}  
	};//this object will be serialized, everything you put in here will be serialized

	return j_object.dump();
}

void SerializationFacade::deserialize_example_guy(std::string& guystring, ExampleGuy& guy) const
{
	nlohmann::json j_object = nlohmann::json::parse(guystring);

	guy.age = static_cast<int>(j_object["guy"]["age"]);
}

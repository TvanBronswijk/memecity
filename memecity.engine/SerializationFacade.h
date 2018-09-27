#ifndef _SERIALIZATIONFACADE_H
#define _SERIALIZATIONFACADE_H
#include <string>
#include "ExampleGuy.h"

class SerializationFacade
{
public:
	static std::string serialize_example_guy(ExampleGuy& guy);
	void deserialize_example_guy(std::string& guystring, ExampleGuy& guy) const;
};

#endif
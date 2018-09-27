#pragma once
#include <string>

class ExampleGuy {
private:
	int age;
public:
	ExampleGuy() { age = 0; }
	friend class SerializationFacade;	 // Friend Class 
};



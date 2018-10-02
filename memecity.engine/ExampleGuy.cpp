#include "ExampleGuy.h"



example_guy::example_guy()
= default;


example_guy::~example_guy()
= default;

std::map<int, std::any> example_guy::to_map()
{
	std::map<int, std::any> map;
	return map;
}

void example_guy::from_map(std::map<int, std::any> map)
{
}


#ifndef _EXAMPLEGUY
#define _EXAMPLEGUY
#include "Serializable.h"

class example_guy :
	public Serializable
{
public:
	example_guy();
	~example_guy();
	std::string name;
	int age;
	float money;
	bool friends;
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
private:
	int legCount;
};


#endif
#pragma once
#include <map>
#include <any>

class SerializableClass
{
public:
	virtual std::map<int, std::any>  to_map() =0;
	virtual void from_map(std::map<int, std::any> map)=0;

};


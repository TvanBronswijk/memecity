#pragma once
#include <map>
#include <any>
#include "AnyExtension.h"

class SerializableClass
{
public:
	virtual std::map<std::string, AnyExtension>  to_map() =0;
	virtual void from_map(std::map<std::string, AnyExtension> map)=0;

};


#ifndef _SERIALIZABLE_H
#define _SERIALIZABLE_H
#include <map>
#include <any>

class Serializable
{
public:
	virtual std::map<std::string, std::any>  to_map() =0;
	virtual void from_map(std::map<std::string, std::any> map)=0;

};

#endif
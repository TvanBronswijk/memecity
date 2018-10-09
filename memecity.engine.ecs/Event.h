#ifndef _EVENT_H
#define  _EVENT_H
#include <iostream>

struct Event {
	virtual std::string get_type();
};

#endif

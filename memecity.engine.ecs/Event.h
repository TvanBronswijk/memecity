#ifndef _EVENT_H
#define  _EVENT_H
#include <iostream>

struct Event {
	///<summary>Get the type of the event for filtering.</summary>
	virtual std::string get_type() = 0;
};

#endif

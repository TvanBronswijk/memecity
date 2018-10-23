#ifndef _EVENT_ARGS_H
#define  _EVENT_ARGS_H
#include <iostream>

struct EventArgs {

	virtual std::string get_type() = 0;
	virtual ~EventArgs() {}
};

#endif

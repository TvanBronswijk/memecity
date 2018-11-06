#ifndef _SYSTEM_H
#define  _SYSTEM_H
#include <iostream>
#include "EventArgs.h"

namespace ecs {
	using system_typetoken = const char*;

	class EntityManager;
	class System {
	protected:
	public:
		System() {};
		System(const System &) = delete;
		System(System &&) = delete;

		///<summary>Get a type token.</summary>
		virtual system_typetoken get_type_token() = 0;

		///<summary>Do the activity of the System.</summary>
		virtual void run(EntityManager &em) = 0;

		virtual ~System() {}
	};
};




#endif
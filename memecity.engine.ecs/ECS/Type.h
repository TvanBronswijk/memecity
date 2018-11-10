#ifndef _ECS_TYPE_H
#define  _ECS_TYPE_H
#include <typeindex>
namespace ecs {
	using TypeToken = std::type_index;
	template<class T>
	TypeToken token() { return typeid(T); };
};
#endif

#ifndef _EVENT_H
#define  _EVENT_H
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>
#include "EntityManager.h"

namespace ecs {
	namespace eventing {
		template<typename TEventArgs>
		class Event {
		protected:
			std::vector<std::tuple<System&, std::function<void(EntityManager&, TEventArgs)>>> subscribers;
		public:
			Event() {};
			
			///<summary>subscribe to an event</summary>
			virtual void bind(System& system, std::function<void(EntityManager&, TEventArgs)> function)
			{
				subscribers->add(std::make_tuple(system, function));
			}

			///<summary>Fire the event with args.</summary>
			virtual void fire(EntityManager& em, TEventArgs ea)
			{
				for (auto sub : subscribers) {
					auto[system, function] = sub;
					std::bind(function, std::ref(system))(em, ea);
				}
			}

			virtual ~Event() {};
		};
	};
};

#endif

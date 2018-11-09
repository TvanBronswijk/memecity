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
			std::vector<std::function<void(EntityManager&, TEventArgs)>> subscribers;
		public:
			Event() = default;

			///<summary>subscribe to an event</summary>
			virtual void bind(std::function<void(EntityManager&, TEventArgs)> function)
			{
				subscribers.push_back(function);
			}

			///<summary>Fire the event with args.</summary>
			virtual void fire(EntityManager& em, TEventArgs ea) const
			{
				for (auto sub : subscribers) {
					sub(em, ea);

				}
			}

			virtual ~Event() {};
		};
	};
};

#endif

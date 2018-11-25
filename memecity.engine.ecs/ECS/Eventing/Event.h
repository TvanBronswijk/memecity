#ifndef _EVENT_H
#define  _EVENT_H
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>
#include "..\EntityManager.h"

namespace memecity::engine::ecs::eventing {
	template<typename TEventArgs>
		class Event {
			using Subscriber = std::function<void(EntityManager&, TEventArgs)>;

		protected:
			std::vector<Subscriber> subscribers;
		public:
			Event() = default;

			///<summary>subscribe to an event</summary>
			virtual void bind(Subscriber s) { subscribers.push_back(s); }
			///<summary>subscribe to an event</summary>
			virtual void operator += (Subscriber s) { bind(s); }

			///<summary>Fire the event with args.</summary>
			virtual void fire(EntityManager& em, TEventArgs ea) const
			{
				for (auto& subscriber : subscribers) {
					subscriber(em, ea);

				}
			}

			virtual ~Event() {};
		};
};

#endif

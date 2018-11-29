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

		template<class TEventArgs>
		void bind(Event<TEventArgs> &event, void(*func)(EntityManager&, TEventArgs)) {
			event += std::bind(func, std::placeholders::_0, std::placeholders::_1);
		}

		template<class TEventArgs, class System>
		void bind(Event<TEventArgs> &event, System *sys, void(System::*func)(EntityManager&, TEventArgs)) {
			event += std::bind(func, sys, std::placeholders::_1, std::placeholders::_2);
		}
};

#endif

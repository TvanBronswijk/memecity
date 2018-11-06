#ifndef _EVENT_H
#define  _EVENT_H
#include <functional>
#include <iostream>
#include <vector>
#include "EntityManager.h"

namespace ecs {
	namespace eventing {
		template<typename T>
		class EventHandler {
		protected:
			//std::vector<std::function<EntityManager&(), T()>&> subscribers;
		public:
			EventHandler() {};

			/*virtual += (std::function<EntityManager&(), T()>& lambda) override
			{
				subscribers->add(lambda);
			}

			///<summary>Fire the event with args.</summary>
			virtual void Invoke(EntityManager& em, T ea)
			{
				for (auto s : subscribers)
					s(em, ea);
			}*/

			virtual ~EventHandler() {};
		};
	};
};

#endif

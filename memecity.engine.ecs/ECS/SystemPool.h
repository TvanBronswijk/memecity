#ifndef _SYSTEM_POOL_H
#define  _SYSTEM_POOL_H
#include <unordered_map>
#include <memory>
#include "EntityManager.h"
#include "Eventing\Event.h"
#include "System.h"
#include "Type.h"

namespace memecity::engine::ecs {
	class SystemPool {
	private:
		std::unordered_map<System::Scope, std::unordered_map<TypeToken, std::unique_ptr<System>>> systems;
	public:
		SystemPool() = default;
		SystemPool(SystemPool&& em) = default;
		SystemPool& operator=(SystemPool&& em) = default;
		~SystemPool() = default;

		///<summary>Register a system to the EntityManager.</summary>
		template<class S, class... Args>
		S& create_system(System::Scope scope = System::update, Args&&... args)
		{
			static_assert(std::is_convertible<S*, System*>::value, "This function can only construct concrete subclasses of System");
			static_assert(std::is_constructible<S, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			systems[scope][token<S>()] = std::make_unique<S>(std::forward<Args>(args)...);
			auto& new_system = *(static_cast<S*>(systems[scope][token<S>()].get()));
			return new_system;
		}

		///<summary>Get a system of a specific subtype.</summary>
		template<class S>
		S* get_system(System::Scope scope = System::update) {
			auto it = systems[scope].find(token<S>());
			if (it == systems[scope].end()) {
				return nullptr;
			}
			return *it;
		}

		///<summary>Run all systems.</summary>
		void update(EntityManager& em,float dt, System::Scope scope = System::update)
		{
			for (auto& pair : systems[scope]) {
				pair.second->run(em,dt);
			}
		}
	};
};
#endif

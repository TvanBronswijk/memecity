#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include <memory>
#include <stack>
#include <mutex>
#include "..\Exceptions.h"

namespace memecity::engine::state {
	class State;
	class StateManager {
	private:
		std::mutex _mutex;

		std::stack<std::unique_ptr<State>> _stack;
		void exit() const;
		void load() const;
		void enter() const;
	public:
		StateManager() = default;
		template<class T, class ... Args>
		void create_state(Args&& ... args) {
			static_assert(std::is_convertible<T*, State*>::value, "This function can only construct concrete subclasses of State");
			static_assert(std::is_constructible<T, StateManager&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");

			exit();
			_stack.push(std::make_unique<T>(*this, std::forward<Args>(args)...));
			load();
			enter();
		}
		void pop(int count = 1);
		template<class T, class ... Args>
		void swap(Args&& ... args) {
			if (_stack.size() <= 0) {
				throw exceptions::MemeException(exceptions::Level::error, "Statemachine stack is empty while trying to swap.");
			}
			pop();
			create_state<T>(std::forward<Args>(args)...);
		}
		State* current_state() const;
		
		void update(float dt);
		void draw();
	};
}
#endif

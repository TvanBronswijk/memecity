#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include <memory>
#include <stack>
#include "../../StateContext.h"

namespace memecity::engine::state {
	class State;
	class StateMachine {
	private:
		std::stack<std::unique_ptr<State>> _stack;
		void init() const;
	public:
		StateMachine() = default;
		template<class T, class ... Args>
		void create_state(Args&& ... args) {
			static_assert(std::is_convertible<T*, State*>::value, "This function can only construct concrete subclasses of State");
			static_assert(std::is_constructible<T, StateMachine&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			_stack.push(std::make_unique<T>(*this, std::forward<Args>(args)...));
			init();
		}
		void pop(int items = 1) {
			for (int i = 0; i < items; i++) 
			{
				_stack.pop();
			}
		}
		State& current_state() const {
			return *(_stack.top());
		}

		void update(float dt) const;
		void draw() const;
	};
}
#endif

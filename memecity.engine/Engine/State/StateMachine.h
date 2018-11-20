#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include <memory>
#include <stack>
#include "State.h"
namespace memecity::engine::state {
	class StateMachine {
	private:
		std::stack<std::unique_ptr<State>> _stack;
	public:
		StateMachine() = default;
		template<class T, class ... Args>
		void create_state(Args&& ... args) {
			_stack.push(std::make_unique<T>(std::forward<Args>(args)...));
			current_state().init();
		}
		void pop() {
			_stack.pop();

		}
		State& current_state() {
			return *(_stack.top());
		}

		void update(float dt) {
			current_state().update(dt);
		}
		void draw() {
			current_state().draw();
		}
	};
}
#endif

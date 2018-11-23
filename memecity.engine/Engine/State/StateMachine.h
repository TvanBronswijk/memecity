#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include <memory>
#include <stack>

namespace memecity::engine::state {
	class State;
	class StateMachine {
	private:
		std::stack<std::unique_ptr<State>> _stack;
		void exit() const;
		void load() const;
		void enter() const;
	public:
		StateMachine() = default;
		template<class T, class ... Args>
		void create_state(Args&& ... args) {
			static_assert(std::is_convertible<T*, State*>::value, "This function can only construct concrete subclasses of State");
			static_assert(std::is_constructible<T, StateMachine&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");

			exit();
			_stack.push(std::make_unique<T>(*this, std::forward<Args>(args)...));
			load();
			enter();
		}
		void pop(int items = 1);
		State* current_state() const;
		void update(float dt) const;
		void draw() const;
	};
}
#endif

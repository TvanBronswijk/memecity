#include "StateMachine.h"
#include "State.h"

namespace memecity::engine::state {
	void StateMachine::init() const {
		current_state().on_load();
		current_state().on_enter();
	}

	void StateMachine::pop(int items)
	{
		for (int i = 0; i < items; i++)
		{
			current_state().on_exit();
			_stack.pop();
		}
		current_state().on_enter();
	}

	State & StateMachine::current_state() const
	{
		return *(_stack.top());
	}

	void StateMachine::update(float dt) const {
		current_state().update(dt);
	}

	void StateMachine::draw() const {
		current_state().draw();
	}
}

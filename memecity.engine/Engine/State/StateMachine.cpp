#include "StateMachine.h"
#include "..\Exceptions.h"
#include "State.h"

namespace memecity::engine::state {

	void StateMachine::exit() const
	{
		if (_stack.size() > 0) {
			current_state()->on_exit();
		}		
	}

	void StateMachine::enter() const
	{
		if (_stack.size() > 0) {
			current_state()->on_enter();
		}
	}

	void StateMachine::load() const
	{
		if (_stack.size() > 0) {
			current_state()->on_load();
		}
	}

	void StateMachine::pop(int items)
	{
		for (int i = 0; i < items; i++)
		{
			if (_stack.size() <= 0) {
				throw exceptions::MemeException(exceptions::Level::error, "Statemachine Stack is empty while pop queue is not.");
			}

			exit();
			_stack.pop();
		}
		enter();
	}

	State* StateMachine::current_state() const
	{
		if (_stack.size() > 0)
			return _stack.top().get();
		return nullptr;
	}

	void StateMachine::update(float dt) const {
		current_state()->update(dt);
	}

	void StateMachine::draw() const {
		current_state()->draw();
	}
}

#include "StateMachine.h"
#include "State.h"

namespace memecity::engine::state {
	void StateMachine::init() const {
		current_state().init();
	}

	void StateMachine::update(float dt) const {
		current_state().update(dt);
	}

	void StateMachine::draw() const {
		current_state().draw();
	}
}

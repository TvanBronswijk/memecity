#include "StateMachine.h"
#include "State.h"

namespace memecity::engine::state {
	void StateMachine::init() {
		current_state().init();
	}

	void StateMachine::update(float dt) {
		current_state().update(dt);
	}

	void StateMachine::draw() {
		current_state().draw();
	}
}

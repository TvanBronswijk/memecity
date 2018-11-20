#ifndef _STATE_MACHINE_STATE_H
#define _STATE_MACHINE_STATE_H
#include "StateMachine.h"

namespace memecity::engine::state {
	class State {
	protected:
		StateMachine& _state_machine;
	public:
		State(StateMachine& sm) : _state_machine(sm) {};
		State(const State &) = delete;
		State(State &&) = delete;
		State& operator=(const State&) = delete;
		State& operator=(State&&) = delete;
		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual void back() { _state_machine.pop(); }
		virtual ~State() = default;
	};
}

#endif

#ifndef _STATE_MACHINE_STATE_H
#define _STATE_MACHINE_STATE_H
#include "StateMachine.h"

namespace memecity::engine::state {
	class State {
	protected:
		StateMachine& _state_machine;
		StateContext& _context;


	public:
		State(StateMachine& sm, StateContext& sc) 
		: _state_machine(sm), _context(sc) {}

		State(const State &) = delete;
		State(State &&) = delete;
		State& operator=(const State&) = delete;
		State& operator=(State&&) = delete;
		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual void back() const { _state_machine.pop(); }
		virtual ~State() = default;

		StateContext& get_context() 
		{
			return _context;
		}
	};
}

#endif

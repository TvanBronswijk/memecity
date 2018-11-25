#ifndef _STATE_MACHINE_STATE_H
#define _STATE_MACHINE_STATE_H
#include "StateManager.h"
#include "..\..\MemeEngine.h"

namespace memecity::engine::state {
	class State {
	protected:
		StateManager* _state_machine;
	public:
		State(StateManager& sm)
		: _state_machine(&sm) {}

		State(const State &) = delete;
		State(State &&) = delete;
		State& operator=(const State&) = delete;
		State& operator=(State&&) = delete;
		virtual void on_load() {};
		virtual void update(float dt) {};
		virtual void draw() {};
		virtual void on_enter() {};
		virtual void on_exit() {};
		
		template<class T, class ...Args>
		void next(Args&&... args) const { _state_machine->create_state<T>(std::forward<Args>(args)...); }
		void back(int i = 1) const { _state_machine->pop(i); }
		virtual ~State() = default;
	};
}

#endif

#ifndef _STATE_MACHINE_STATE_H
#define _STATE_MACHINE_STATE_H
#include "StateManager.h"
#include "StateContext.h"

namespace memecity::engine::state {
	class State {
	protected:
		StateManager* _state_machine;
		StateContext* _context;
	public:
		State(StateManager& sm, StateContext& sc) 
		: _state_machine(&sm), _context(&sc) {}

		State(const State &) = delete;
		State(State &&) = delete;
		State& operator=(const State&) = delete;
		State& operator=(State&&) = delete;
		virtual void on_load() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual void on_enter() = 0;
		virtual void on_exit() = 0;
		
		template<class T, class ...Args>
		void next(Args&&... args) const { _state_machine->create_state<T>(std::forward<Args>(args)...); }
		void back(int i = 1) const { _state_machine->pop(i); }

		virtual ~State() = default;

		StateContext& get_context() 
		{
			return *_context;
		}
	};
}

#endif

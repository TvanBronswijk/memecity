#ifndef _STATE_MACHINE_STATE_H
#define _STATE_MACHINE_STATE_H

namespace memecity::engine::state {
	class State {
	public:
		State() = default;
		State(const State &) = delete;
		State(State &&) = delete;
		State& operator=(const State&) = delete;
		State& operator=(State&&) = delete;
		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual ~State() = default;
	};
}

#endif

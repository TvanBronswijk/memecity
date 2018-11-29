#include "StateManager.h"
#include "State.h"

namespace memecity::engine::state {

	void StateManager::exit() const
	{
		if (_stack.size() > 0) {
			current_state()->on_exit();
		}		
	}

	void StateManager::enter() const
	{
		if (_stack.size() > 0) {
			current_state()->on_enter();
		}
	}

	void StateManager::load() const
	{
		if (_stack.size() > 0) {
			current_state()->on_load();
		}
	}

	void StateManager::pop(int count)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		for (int i = 0; i < count; i++)
		{
			if (_stack.size() <= 0) {
				throw exceptions::MemeException(exceptions::Level::error, "Statemachine Stack is empty while pop queue is not.");
			}

			exit();
			_stack.pop();
		}
		enter();
	}

	State* StateManager::current_state() const
	{
		if (_stack.size() > 0)
			return _stack.top().get();
		return nullptr;
	}

	void StateManager::update(float dt) {
		current_state()->update(dt);
	}

	void StateManager::draw() {
		std::unique_lock<std::mutex> lock(_mutex, std::defer_lock);
		if (lock.try_lock()) {
			current_state()->draw();
			lock.unlock();
		}
	}
}

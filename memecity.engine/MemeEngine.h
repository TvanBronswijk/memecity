#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H
#include <functional>
#include "Engine\InputManager.h"
#include "Engine\MultimediaManager.h"
#include "Engine\StorageManager.h"


namespace memecity::engine {
	namespace sdl {
		class TimerFacade;
	};

	template<class T>
	using Runnable = std::function<T()>;
	enum class Threading {
		///<summary>[EXPERIMENTAL]</summary>
		multithreaded, 
		singlethreaded
	};

	class MemeEngine
	{
	private:
		int run_multi();
		int run_single();

		Runnable<int> _runnable;
	protected:
		StorageManager storage_manager;
		MultimediaManager multimedia_manager{ false };
		InputManager input_manager{};
		sdl::TimerFacade timer;

		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;

		virtual void set_runnable(Runnable<int> runnable)
		{
			_runnable = runnable;
		}

	public:
		int run(Threading flag = Threading::singlethreaded);
		MemeEngine();
		 MultimediaManager& get_multimedia_manager()
		{
			return multimedia_manager;
		}
		InputManager& get_input_manager()
		{
			return input_manager;
		}
		sdl::TimerFacade& get_timer()
		{
			return timer;
		}
	};
}

#endif

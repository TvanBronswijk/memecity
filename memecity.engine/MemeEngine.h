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

	enum class Threading {
		///<summary>[EXPERIMENTAL]</summary>
		multithreaded, 
		singlethreaded
	};

	class MemeEngine
	{
		template<class T>
		using Runnable = std::function<T(MemeEngine&)>;
	private:
		Runnable<int> _runnable;
	protected:
		StorageManager storage_manager;
		MultimediaManager multimedia_manager{ false };
		InputManager input_manager{};
		sdl::TimerFacade timer;
		virtual void init() = 0;
	public:
		MemeEngine() = default;
		~MemeEngine() = default;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		int run(Threading flag = Threading::singlethreaded);
		int run(Runnable<int> runnable);
		virtual void set_runnable(Threading flag);
		virtual void set_runnable(Runnable<int> runnable);
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

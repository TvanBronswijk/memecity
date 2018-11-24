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
		///<summary>Initialization logic</summary>
		virtual void init() = 0;
	public:
		MemeEngine() = default;
		~MemeEngine() = default;
		///<summary>Update game logic and handle user input</summary>
		virtual void update(float dt) = 0;
		///<summary>Render textures</summary>
		virtual void draw() = 0;
		///<summary>Start the game. Optional Threading flag allows you to choose between multithreaded and singlethreaded runner. Defaults to singlethreaded.</summary>
		int run(Threading flag = Threading::singlethreaded);
		///<summary>Start the game. Custom runner.</summary>
		int run(Runnable<int> runnable);
		///<summary>Set one of the default runners. To be used for runtime switching of runner.</summary>
		virtual void set_runnable(Threading flag);
		///<summary>Set to a custom runner. To be used for runtime switching of runner.</summary>
		virtual void set_runnable(Runnable<int> runnable);

		 MultimediaManager& get_multimedia_manager() { return multimedia_manager; }
		InputManager& get_input_manager() { return input_manager; }
		sdl::TimerFacade& get_timer() { return timer; }
	};
}

#endif

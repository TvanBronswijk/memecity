#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H

#include <functional>
#include <iostream>
#include <thread>
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
		struct Context
		{
		private:
			MultimediaManager* multimedia_manager;
			InputManager* input_manager;
			sdl::TimerFacade* timer;
			StorageManager* storage_manager;
			MemeEngine* engine;

		public:
			Context(MultimediaManager& mm, InputManager& im, sdl::TimerFacade& t, StorageManager& stm, MemeEngine& engine)
				: multimedia_manager(&mm), input_manager(&im), timer(&t), storage_manager(&stm), engine(&engine) {}
			Context(MemeEngine& engine)
				: multimedia_manager(&engine.multimedia_manager), input_manager(&engine.input_manager), timer(&engine.timer), storage_manager(&engine.storage_manager), engine(&engine) {}
			virtual ~Context() = default;

			MultimediaManager& get_multimedia_manager() { return *multimedia_manager; }
			InputManager& get_input_manager() { return *input_manager; }
			sdl::TimerFacade& get_timer() { return *timer; }
			StorageManager& get_storage_manager() { return *storage_manager; }
			MemeEngine& get_engine() { return *engine; }
		};

		StorageManager storage_manager;
		MultimediaManager multimedia_manager;
		InputManager input_manager;
		serialization::SerializationFacade serialization_facade;
		sdl::TimerFacade timer;
		std::unique_ptr<Context> _context;

		bool get_fps_trigger = false;
		bool display_game_speed = false;

		using FpsSubscriber = std::function<void(bool enabled,int fps)>;
		using GameSpeedSubscriber = std::function<void(bool enabled, float fps)>;

		std::vector<FpsSubscriber> fps_subscribers;
		std::vector<GameSpeedSubscriber> game_speed_subscribers;

		float game_speed_modifier = 1.0f;

	public:

		void set_games_speed_modifier(float new_speed)
		{
			this->game_speed_modifier = new_speed;
			if (display_game_speed) {
				for (auto& subscriber : game_speed_subscribers) {
					subscriber(true, new_speed);
				}
			}
		}

		float get_game_speed_modifier()
		{
			return this->game_speed_modifier;
		}

		void bind_fps(FpsSubscriber s)
		{
			fps_subscribers.push_back(s);
			get_fps_trigger = true;
		}
		void bind_game_speed(GameSpeedSubscriber s)
		{
			game_speed_subscribers.push_back(s);
			display_game_speed = true;
			for (auto& subscriber : game_speed_subscribers) {
				subscriber(true, game_speed_modifier);
			}
		}
		void disable_display_gamespeed()
		{
			
			for (auto& subscriber : game_speed_subscribers) {
				subscriber(false, 0.0f);
			}
			game_speed_subscribers.clear();			
			display_game_speed = false;
		}
		void disable_calculate_fps()
		{
			for (auto& subscriber : fps_subscribers) {
				subscriber(false, 0);
			}
			fps_subscribers.clear();			
			get_fps_trigger = false;
		}
		MemeEngine() : storage_manager(serialization_facade), multimedia_manager(false), input_manager(), timer() {
			_context = std::make_unique<Context>(*this);
		};

		~MemeEngine() = default;
		///<summary>Start the game. Optional Threading flag allows you to choose between multithreaded and singlethreaded runner. Defaults to singlethreaded.</summary>
		int run(Threading flag = Threading::singlethreaded);
		///<summary>Start the game. Custom runner.</summary>
		int run(Runnable<int> runnable);
		///<summary>Set one of the default runners. To be used for runtime switching of runner.</summary>
		virtual void set_runnable(Threading flag);
		///<summary>Set to a custom runner. To be used for runtime switching of runner.</summary>
		virtual void set_runnable(Runnable<int> runnable);

		///<summary>Initialization logic</summary>
		virtual void init() = 0;
		///<summary>Update game logic and handle user input</summary>
		virtual void update(float dt) = 0;
		///<summary>Render textures</summary>
		virtual void draw() = 0;

		virtual Context& get_context() { return *_context; }

		friend int multithreaded(memecity::engine::MemeEngine& engine);
		friend int singlethreaded(memecity::engine::MemeEngine& engine);
	};
}

#endif

﻿#ifndef _AUDIOFACADE_H
#define _AUDIOFACADE_H
#include <memory>
#include <string>

namespace memecity::engine::sdl {
	class RawSfxWrapper;
	class RawMusicWrapper;

	class AudioFacade
	{
	public:
		///<summary>Initializes the SDL Audio.</summary>
		bool init() const;

		///<summary>Open the SDL audio mixer with a given audio format.</summary>
		void open_audio(int frequency, int channels, int chunksize) const;

		///<summary>Play a sound effect with a given amount of repeats, volume and the selected channel.</summary>
		void play_sound_effect(const RawSfxWrapper& sound, int repeats, int volume, int channel = 0) const;

		///<summary>Checks if audio is playing on the given channel.</summary>
		bool is_playing(int channel) const;

		///<summary>Play a given background music with a specified volume.</summary>
		void play_background_music(const RawMusicWrapper& music, int volume) const;

		///<summary>If the music is paused, resume. Otherwise pause.</summary>
		void pause_background_music() const;

		///<summary>If background music is playing, stop it.</summary>
		void stop_background_music() const;

		///<summary>Loads texture from path into memory.</summary>
		std::unique_ptr<RawMusicWrapper> load_music(std::string path) const;

		///<summary>Loads a text texture from path into memory.</summary>
		std::unique_ptr<RawSfxWrapper> load_sfx(std::string path) const;

		///<summary>Cleanup audio</summary>
		void close_audio() const;
	};
}

#endif

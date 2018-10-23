#include "MultimediaManager.h"

///<summary>Constructor which initializes the necessary classes.</summary>
MultimediaManager::MultimediaManager(bool is_fullscreen)
{
	graphics_facade = std::make_shared<GraphicsFacade>(is_fullscreen);
	asset_manager = std::make_unique<AssetManager>(graphics_facade);
	audio_facade = std::make_unique<AudioFacade>();
}

///<summary>Initializes Graphics and Audio facades 
/// Returns whether this succeeded or not.</summary>
bool MultimediaManager::init() const
{	
	if (graphics_facade->init() && audio_facade->init())
	{
		audio_facade->open_audio(44100, 2, 4096);
		return true;
	}

	return false;
}

///<summary>Gets the sound based on filename and plays it through the AudioFacade.</summary>
void MultimediaManager::play_background_music(std::string name, int volume) const
{
	const auto music = asset_manager->get_music(name);
	audio_facade->play_background_music(music, volume);
}

///<summary>Gets the sound effect based on filename and plays it through the AudioFacade.</summary>
void MultimediaManager::play_sound_effect(std::string name, int repeats, int volume, int channel) const
{
	const auto sound = asset_manager->get_sfx(name);
	audio_facade->play_sound_effect(sound, repeats, volume, channel);
}

///<summary>Pauses background music.</summary>
void MultimediaManager::pause_background_music() const
{	
	audio_facade->pause_background_music();
}

///<summary>Clears the graphics.</summery>
void MultimediaManager::clear_graphics() const
{
	graphics_facade->clear();
}

///<summary>Render the graphics.</summary>
void MultimediaManager::render_graphics() const
{
	graphics_facade->render();
}

///<summary>Get a texture.</summary>
std::shared_ptr<Texture> MultimediaManager::get_texture(std::string filename)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_texture(filename));
}

///<summary>Get a texture.</summary>
std::shared_ptr<Texture> MultimediaManager::get_texture(std::string filename, int x, int y, int width, int height)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_texture(filename), x, y, width, height);
}

///<summary>Gets a text texture.</summary>
std::shared_ptr<Texture> MultimediaManager::get_text_texture(std::string text, std::string font_path, int size, Color color)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_text(text, font_path, size, color.get_sdl_color()));
}

int MultimediaManager::get_screen_width()
{
	return graphics_facade->screen_width;
}

int MultimediaManager::get_screen_height()
{
	return graphics_facade->screen_height;
}

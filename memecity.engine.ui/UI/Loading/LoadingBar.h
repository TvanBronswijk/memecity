#ifndef _UI_LOADING_BAR_H
#define  _UI_LOADING_BAR_H
#include <string>

namespace memecity::engine::ui::loading {
	template<class T>
	class uLoadingBar
	{
	private:
		MultimediaManager* multimedia_manager;
		const char* _text;
		T _max;
		T _curr;
	public:
		uLoadingBar(MultimediaManager& multimedia_manager) : multimedia_manager(&multimedia_manager), _text("Loading"), _max(0), _curr(0) {};
		~uLoadingBar() = default;
		void render() {
			auto text_texture = multimedia_manager->get_text_texture(_text, "Minecraftia-Regular.ttf", 36, { 255,255,255 });
			text_texture->set_position({ multimedia_manager->get_screen_width() / 2.0f, 200.0f });
			multimedia_manager->render_texture(*text_texture);

			auto perc_texture = multimedia_manager->get_text_texture(std::to_string((int)(_curr / _max * 100)) + '%', "Minecraftia-Regular.ttf", 24, { 255,255,255 });
			perc_texture->set_position({ multimedia_manager->get_screen_width() / 2.0f, 300.0f });
			multimedia_manager->render_texture(*perc_texture);
		}

		class Listener {
		private:
			uLoadingBar<T>* _lbar;
		public:
			Listener(uLoadingBar<T>& loading_bar) : _lbar(&loading_bar) {}
			~Listener() = default;
			Listener& set_text(const char* text) {
				_lbar->_text = text;
				return *this;
			}
			Listener& set_max_value(T value) {
				_lbar->_max = value;
				return *this;
			}
			Listener& set_current_value(T value) {
				_lbar->_curr = value;
				return *this;
			}

			Listener& increase_current_value(T value) {
				_lbar->_curr += value;
				return *this;
			}
		};

		Listener get_listener() {
			return Listener(*this);
		}
	};
	using LoadingBar = uLoadingBar<float>;
}
#endif
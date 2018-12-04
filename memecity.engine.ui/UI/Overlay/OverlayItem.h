#ifndef _OVERLAY_ITEM_H
#define  _OVERLAY_ITEM_H
#include <Engine/MultimediaManager.h>


namespace memecity::engine::ui::overlay {
	class Overlay;
	template <class  T>
	class OverlayItem
	{
	protected:
		float x;
		float y;
		int size;
		T value;
		Overlay& parent;
		MultimediaManager* multimedia_manager;
	public:
		OverlayItem(MultimediaManager& multimedia_manager, Overlay& parent, T value, int size, float x, float y)
		:x(x), y(y),size(size), value(value), parent(parent), multimedia_manager(&multimedia_manager)
		{
			
		}

		virtual void update(T value) { this->value = value; };
		virtual void render() = 0;

	};
}

#endif